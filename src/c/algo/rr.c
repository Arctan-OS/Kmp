/**
 * @file rr.c
 *
 * @author awewsomegamer <awewsomegamer@gmail.com>
 *
 * @LICENSE
 * Arctan-OS/Kernel - Operating System Kernel
 * Copyright (C) 2023-2025 awewsomegamer
 *
 * This file is part of Arctan-OS/Kernel.
 *
 * Arctan is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @DESCRIPTION
*/
#include "arch/x86-64/config.h"
#ifdef ARC_TARGET_SCHED_RR

#include "arch/interrupt.h"
#include "arch/smp.h"
#include "config.h"
#include "global.h"
#include "lib/atomics.h"
#include "mm/allocator.h"
#include "mp/scheduler.h"
#include "userspace/process.h"
#include "userspace/thread.h"

static ARC_Thread *halt = NULL;
static ARC_Process *halt_proc = NULL;

typedef struct internal_queue_element {
	struct internal_queue_element *next;
	ARC_Thread *thread;
} internal_queue_element;

static internal_queue_element *root = NULL;

typedef struct internal_perproc_state {
	uint64_t ticks;
} internal_perproc_state;

int sched_queue(ARC_Thread *thread) {
	if (thread == NULL) {
		return -1;
	}

	internal_queue_element *e = alloc(sizeof(*e));
	e->thread = thread;
	ARC_ATOMIC_XCHG(&root, &e, &e->next);

	return 0;
}

int sched_dequeue(ARC_Thread *thread) {
	if (thread == NULL) {
		return -1;
	}

	internal_queue_element *c = root;
	internal_queue_element *l = NULL;
	while (c != NULL && c->thread != thread) {
		l = c;
		c = c->next;
	}

	if (c == NULL) {
		return -2;
	}

	internal_queue_element *t = NULL;
	ARC_ATOMIC_XCHG(&l->next, &c->next, &t);

	free(c);

	return 0;
}

static ARC_Thread *sched_get_next_thread() {
	// NOTE: Don't need to waste time to check if
	//       root is NULL, if we made it this far
	//       it is probably not

	internal_queue_element *c = root;

	while (c != NULL) {
		// Synchronize with sched_tick's SFENCE
		ARC_ATOMIC_LFENCE;
		uint32_t state = ARC_ATOMIC_LOAD(c->thread->state);
		if (ARC_ATOMIC_CMPXCHG(&c->thread->state, &state, ARC_THREAD_RUNNING)) {
			return c->thread;
		}

		c = c->next;
	}

	return halt;
}

int sched_tick() {
	ARC_ProcessorDescriptor *desc = smp_get_proc_desc();
	internal_perproc_state *state = desc->scheduler_meta;

	if (state == NULL) {
		desc->scheduler_meta = alloc(sizeof(internal_perproc_state));
		memset(desc->scheduler_meta, 0, sizeof(internal_perproc_state));
		state = desc->scheduler_meta;
	}

	if (state == NULL) {
		return -2;
	}

	int r = 1;

	if (state->ticks > ARC_TICKS_PER_TIMESLICE) {
		ARC_Thread *new = sched_get_next_thread();

		if (desc->thread != NULL && desc->thread != halt) {
			uint32_t expected = ARC_THREAD_RUNNING;
			ARC_ATOMIC_CMPXCHG(&desc->thread->state, &expected, ARC_THREAD_READY);
			ARC_ATOMIC_SFENCE;
		}

		desc->thread = new;

		state->ticks = 0;
		r = 0;
	}

	state->ticks++;

	return r;
}

void sched_yield(ARC_Thread *thread) {
	(void)thread;
}

ARC_Thread *sched_current_thread() {
	ARC_ProcessorDescriptor *proc = smp_get_proc_desc();

	if (proc == NULL) {
		return NULL;
	}

	return proc->thread;
}

void sched_timer_hook(ARC_InterruptFrame *frame) {
	ARC_ProcessorDescriptor *desc = smp_get_proc_desc();
	ARC_Thread *cur = desc->thread;

	if (cur != NULL) {
		// Save old context
		memcpy(&cur->context->frame, frame, sizeof(*frame));
	}

	// TODO: FXSAVE / RSTOR, TCB

	if (sched_tick() == 0) {
		cur = desc->thread;

		// Swap in new context if needed
		memcpy(frame, &cur->context->frame, sizeof(*frame));
	}

	interrupt_end();
}

ARC_DEFINE_IRQ_HANDLER(sched_timer_hook);

int init_scheduler() {
	halt_proc = process_create(false, NULL);

	if (halt_proc == NULL) {
		ARC_DEBUG(ERR, "Could not create holding process\n");
		return -1;
	}

	halt = thread_create(halt_proc, (void *)smp_hold, PAGE_SIZE);

	if (halt == NULL) {
		ARC_DEBUG(ERR, "Could not create holding thread\n");
		return -2;
	}

	ARC_DEBUG(INFO, "Initialized round robin scheduler\n");

	return 0;
}

#endif
