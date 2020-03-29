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


void usleep(__useconds_t usec)
{
    syscall(SYS_SLEEP, usec);
}

int __exec(char *name, const char **argv, const char **env, int fds[3])
{
    return syscall(SYS_PFORK, 0, name, argv, env, fds);
}

_Noreturn void exit(int res)
{
    for (;;)
        syscall(SYS_EXIT, res, 0);
}

int fork()
{
    return -1;
}

static void thrd_run_impl_(thrd_start_t func, void *arg)
{
    int res = func(arg);
    if (res == 0)
        thrd_detach(thrd_current());
    thrd_exit(res);
}

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
    void *params[2];   // void *stack = mmap();
    params[0] = func;
    params[1] = arg;
    long ret = syscall(SYS_TFORK, 0, &thrd_run_impl_, &params, sizeof(params), NULL);
    return ret == 0 ? thrd_error : thrd_success;
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
    for (;;)
        syscall(SYS_EXIT, res, -1);
}

int thrd_join(thrd_t thr, int *res)
{
    // Use cond on stack
    return thrd_error;
}

void thrd_sleep(const struct timespec *restrict time_point, struct timespec *restrict remaining)
{
    usleep(time_point->tv_sec * 1000000LL + time_point->tv_nsec / 1000LL);
}

void thrd_yield(void)
{
    syscall(SYS_SLEEP, -1);
}

