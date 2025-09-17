/**
 * @file scheduler.c
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
#include "mp/scheduler.h"
#include "userspace/process.h"

int sched_queue_proc(ARC_Process *proc) {
        if (proc == NULL) {
                return -1;
        }

        ARC_ThreadElement *c = proc->threads;

        while (c != NULL) {
                sched_queue(c->t);
                c = c->next;
        }

        return 0;
}

int sched_dequeue_proc(ARC_Process *proc) {
        if (proc == NULL) {
                return -1;
        }

        ARC_ThreadElement *c = proc->threads;

        while (c != NULL) {
                sched_dequeue(c->t);
                c = c->next;
        }

        return 0;
}
