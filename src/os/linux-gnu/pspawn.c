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
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>

int execve(const char *filename, char *const argv[], char *const envp[]);
_Noreturn void _Exit(int code);


__pid_t pspawn(const char *exec, int *fdset, sigset_t *set, char *const *args, char *const *envs)
{
    __pid_t pid = fork();
    if (pid != 0)
        return pid;

    // Redirect iostream

    // Change signals

    execve(exec, args, envs);
    _Exit(-1);
}
