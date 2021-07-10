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
#ifndef __SIGNAL_H
#define __SIGNAL_H 1

#include <bits/cdefs.h>
#include <bits/signum.h>
#include <bits/signal.h>
#include <bits/types.h>

__STDC_GUARD


#define SIG_BLOCK     0
#define SIG_UNBLOCK   1
#define SIG_SETMASK   2

#define SIG_DFL  ((void (*)(int)) 0)
#define SIG_ERR  ((void (*)(int))-1)
#define SIG_IGN  ((void (*)(int)) 1)

int kill(__pid_t pid, int signum);
sighandler_t signal(int signum, sighandler_t handler);
int raise(int signum);


struct sigaction;

int sigaction(int signum, const struct sigaction *restrict newsa,
              struct sigaction *restrict oldsa);

int sigprocmask(int op, const sigset_t *restrict newset, sigset_t *restrict oldset);


__STDC_END

#endif  /* __SIGNAL_H */
