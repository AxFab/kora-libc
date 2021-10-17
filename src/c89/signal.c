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
#include <unistd.h>

sigset_t __sigset_all = ~0ULL;
sigset_t __sigset_app = ~0ULL;

sighandler_t signal(int signum, sighandler_t handler)
{
    struct sigaction sa_old;
    struct sigaction sa = {
        .sa_handler = handler,
        // .sa_flags = SA_RESTART,
    };

    if (sigaction(signum, &sa, &sa_old) < 0)
        return SIG_ERR;
    return sa_old.sa_handler;
}

int raise(int signum)
{
    sigset_t set;
    sigprocmask(SIG_BLOCK, &__sigset_app, &set);
    int ret = kill(getpid(), signum);
    sigprocmask(SIG_SETMASK, &set, NULL);
    return ret;
}
