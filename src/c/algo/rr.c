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
#ifdef ARC_TARGET_SCHED_RR

#include "arch/smp.h"
#include "config.h"
#include "global.h"
#include "lib/atomics.h"
#include "mp/scheduler.h"

static struct ARC_ProcessEntry *current_process = NULL;
static struct ARC_ProcessEntry *begin_process = NULL;

static uint64_t ticks = 0;

int sched_queue(ARC_Thread *thread) {
	/*
	if (proc == NULL) {
		return -1;
	}

	(void)priority;

	struct ARC_ProcessEntry *entry = alloc(sizeof(*entry));

	if (entry == NULL) {
		return -2;
	}

	entry->process = proc;

	struct ARC_ProcessEntry *temp = entry;
	struct ARC_ProcessEntry *expected = NULL;
	struct ARC_ProcessEntry *current = current_process;

	ARC_ATOMIC_LFENCE;

	if (ARC_ATOMIC_CMPXCHG(&current_process, &expected, temp)) {
		begin_process = entry;
	} else {
		ARC_ATOMIC_XCHG(&current->next, &temp, &entry->next);
		ARC_ATOMIC_XCHG(&entry->prev, &current, &temp);
	}
*/
	return 0;
}

int sched_dequeue(ARC_Thread *thread) {
	/*
	if (proc == NULL){
		return -1;
	}

	void *tmp = NULL;

	ARC_ATOMIC_XCHG(&proc->prev->next, &proc->next, (struct ARC_ProcessEntry **)&tmp);
	if (proc->next != NULL) {
		ARC_ATOMIC_XCHG(&proc->next->prev, &proc->prev, (struct ARC_ProcessEntry **)&tmp);
	}

	ARC_ATOMIC_SFENCE;

	if (proc == current_process) {
		current_process = proc->next;
	}
*/
	return 0;
}

int sched_tick() {
	if (begin_process == NULL) {
		return -2;
	}

	struct ARC_ProcessorDescriptor *processor = smp_get_proc_desc();

//	if (processor != Arc_BootProcessor) {
//		return -1;
//	}

	ticks++;
	
	int ret = 0;
	
	if (ticks >= ARC_TICKS_PER_TIMESLICE) {
		ARC_ATOMIC_SFENCE;
		if (current_process != NULL) {
//			current_process = current_process->next;
		}
		
		if (current_process == NULL) {
			current_process = begin_process;
		}

		ticks = 0;

		ret = 1;
	}

	return ret;
}

void sched_yield(ARC_Thread *thread) {
	(void)thread;
}

ARC_Thread *sched_current_thread() {
	/*
	struct ARC_ProcessorDescriptor *processor = smp_get_proc_desc();

	if (processor == NULL) {
		return NULL;
	}

	ARC_ATOMIC_SFENCE;
	processor->current_process = current_process;

	if (processor->current_process == NULL) {
		goto null_case;
	}

	struct ARC_Thread *thread = process_get_thread(processor->current_process->process);
	
	if (thread == NULL) {
		null_case:;
		processor->current_process = begin_process;
		thread = begin_process->process->threads;
	}

	return thread;
	*/
	return NULL;
}

int init_scheduler() {
	ARC_DEBUG(INFO, "Initialized round robin scheduler\n");

	return 0;
}

#endif
