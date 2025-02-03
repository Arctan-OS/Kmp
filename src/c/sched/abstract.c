/**
 * @file abstract.c
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
#include <mp/sched/abstract.h>
#include <global.h>
#include <arch/smp.h>

/*
 * There are three states:
 *  * Last    - Last process ran, has its context stored in a processor
 *              descriptors registers.
 *  * Running - The current processor running, register state is unknown
 *              until timer interrupt asking for a switch.
 *  * Next    - The next process to be run, register state is known at to
 *              be loaded at next timer interrupt.
 * */

struct ARC_Process *temp = NULL;

uint64_t get_current_tid() {
	return ((uint64_t)smp_get_processor_id() << 56) | 1;
}

int yield_cpu(uint64_t tid) {
	if (get_current_tid() == tid) {
		return 0;
	}

//	ARC_DEBUG(INFO, "Yielding CPU\n");

	return 0;
}

int sched_queue(struct ARC_Process *proc, int priority) {
	temp = proc;
	return 0;
}

int sched_tick() {
	return 0;
}

struct ARC_Process *sched_get_current_proc() {
	return temp;
}

int init_scheduler(int type) {
	(void)type;

	ARC_DEBUG(WARN, "Totally initializing scheduler\n");

	return 0;
}
