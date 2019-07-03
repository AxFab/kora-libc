/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2019  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <bits/types.h>
#include <bits/libio.h>
#include <kora/splock.h>
#include <kora/mcrs.h>
#include <kora/syscalls.h>
#include <threads.h>
#include <string.h>
#include <errno.h>


int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
    // void *stack = mmap();
    // thr = stack;
    // stack[0] = desc
    // stack[1] = func
    // stack[2] = arg
    // SYS_FORK(Nothing, &stack[3], thrd_run_impl_);
    return thrd_error;
}

thrd_t thrd_current(void)
{
    return 0;
}

int thrd_detach(thrd_t thr)
{
    return thrd_error;
}

int thrd_equal(thrd_t thr0, thrd_t thr1)
{
    return thr0 == thr1;
}

void thrd_exit(int res)
{
    // SYS_EXIT(res, THREAD);
}

int thrd_join(thrd_t thr, int *res)
{
    // Use cond on stack
    return thrd_error;
}

void thrd_sleep(const struct timespec *restrict time_point)
{
    // SYS_SLEEP(timeout)
}

void thrd_yield(void)
{
    // SYS_SLEEP(-1)
}
