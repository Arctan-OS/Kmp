/**
 * @file scheduler.h
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
#ifndef ARC_MP_SCHEDULER_H
#define ARC_MP_SCHEDULER_H

#include "userspace/thread.h"

enum {
	ARC_THREAD_RUNNING = 0,
	ARC_THREAD_READY,
	ARC_THREAD_SUSPEND
};

// NOTE: Scheduler implementations should define this variable
// extern struct ARC_Process *Arc_SchedCurrentProcess;

int sched_queue(ARC_Thread *thread);
void sched_yield(ARC_Thread *thread);
int sched_dequeue(ARC_Thread *thread);
int sched_tick();
ARC_Thread *sched_current_thread();

int init_scheduler();

#endif
