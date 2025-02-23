/**
 * @file scheduler.h
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
#ifndef ARC_MP_SCHED_ABSTRACT_H
#define ARC_MP_SCHED_ABSTRACT_H

#include <stdint.h>
#include <arch/process.h>

#define ARC_SCHED_PRI_HI 0
#define ARC_SCHED_PRI_LO 8

// NOTE: Scheduler implementations should define this variable
// extern struct ARC_Process *Arc_SchedCurrentProcess;

int sched_queue(struct ARC_Process *proc, int priority);
int sched_dequeue(struct ARC_Process *proc);
int sched_tick();

/**
 * Get the currently running thread ID.
 * */
uint64_t sched_get_current_tid();

struct ARC_Thread *sched_get_current_thread();

/**
 * Yield CPU to desired thread.
 * */
int sched_yield_cpu(uint64_t tid);

int init_scheduler();

#endif
