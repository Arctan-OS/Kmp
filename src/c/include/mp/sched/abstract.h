/**
 * @file abstract.h
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

#define ARC_SCHED_TYPE_RR 0

#define ARC_SCHED_PRI_HI 0
#define ARC_SCHED_PRI_LO 8

/**
 * Get the currently running thread ID.
 * */
uint64_t get_current_tid();

/**
 * Yield CPU to desired thread.
 * */
int yield_cpu(uint64_t tid);

int sched_queue(struct ARC_Process *proc, int priority);
int sched_tick();
struct ARC_Process *sched_get_current_proc();
int init_scheduler(int type);

#endif
