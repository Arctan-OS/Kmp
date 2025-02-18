/**
 * @file rr.c
 *
 * @author awewsomegamer <awewsomegamer@gmail.com>
 *
 * @LICENSE
 * Arctan - Operating System Kernel
 * Copyright (C) 2023-2025 awewsomegamer
 *
 * This file is part of Arctan.
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
//#ifdef ARC_TARGET_SCHED_RR

#include <mp/scheduler.h>
#include <mm/allocator.h>
#include <lib/atomics.h>
#include <arch/smp.h>

#include <global.h>

struct process_entry {
	struct ARC_Process *process;
	struct process_entry *next;
};

static struct process_entry *current_process = NULL;

static ARC_GenericSpinlock list_lock;

static uint64_t ticks = 0;

int sched_queue(struct ARC_Process *proc, int priority) {
	if (proc == NULL) {
		return -1;
	}

	(void)priority;

	struct process_entry *entry = alloc(sizeof(*entry));

	if (entry == NULL) {
		return -2;
	}

	entry->process = proc;

	spinlock_lock(&list_lock);
	if (current_process != NULL) {
		entry->next = current_process->next;
		current_process->next = entry;
	} else {
		entry->next = entry;
		current_process = entry;
	}
	spinlock_unlock(&list_lock);

	return 0;
}

int sched_dequeue(struct ARC_Process *proc) {
	if (proc == NULL) {
		return -1;
	}

	return 0;
}

struct ARC_Thread *sched_tick() {
	return NULL;
}

int sched_yield_cpu(uint64_t tid) {
	(void)tid;

	return 0;
}

struct ARC_Thread *sched_get_current_thread() {
	if (current_process == NULL) {
		return NULL;
	}

	struct ARC_ProcessorDescriptor *processor = smp_get_proc_desc();

	spinlock_lock(&list_lock);

	processor->current_process = current_process->process;
	struct ARC_Thread *thread = process_get_next_thread(current_process->process);

	spinlock_unlock(&list_lock);

	return thread;
}

int init_scheduler() {
	init_static_spinlock(&list_lock);
	ARC_DEBUG(INFO, "Initialized round robin scheduler\n");

	return 0;
}

//#endif
