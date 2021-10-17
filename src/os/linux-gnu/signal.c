/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
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
#include <signal.h>
#include <sys/syscall.h>
#include "syscallno.h"

int kill(__pid_t pid, int sig)
{
    return syscall(SYS_kill, pid, sig);
}


int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
#ifdef SYS_rt_sigprocmask
    return syscall(SYS_rt_sigprocmask, how, set, old, sizeof(sigset_t));
#else
    return syscall(SYS_sigprocmask, how, set, old);
#endif
}


int sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
    return syscall(SYS_sigaction, sig, sa, old);
}
