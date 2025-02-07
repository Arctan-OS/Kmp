/**
 * @file mlfq.c
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
#ifdef ARC_TARGET_SCHED_MLFQ

#include <mp/mflq.h>
#include <mp/scheduler.h>

struct ARC_Process *Arc_SchedCurrentPorcess = NULL;

int sched_queue(struct ARC_Process *proc, int priority) {
	(void)priority;
	Arc_SchedCurrentPorcess = proc;
	return 0;
}

int sched_dequeue(struct ARC_Process *proc) {
	(void)proc;
	return 0;
}

int sched_tick() {
	return 0;
}

int sched_yield_cpu(uint64_t tid) {
	(void)tid;

	return 0;
}

int init_scheduler() {
	return 0;
}

#endif
