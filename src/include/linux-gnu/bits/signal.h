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
#ifndef __BITS_SIGNAL_H
#define __BITS_SIGNAL_H 1


typedef int sig_atomic_t;
typedef unsigned long sigset_t;
typedef struct siginfo siginfo_t;


typedef void (*sighandler_t)(int);
typedef void (*sigaction_t)(int, siginfo_t *, void *);


struct sigaction {
    union {
        sighandler_t sa_handler;
        sigaction_t sa_sigaction;
    } __sa_handler;
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

#define sa_handler   __sa_handler.sa_handler
#define sa_sigaction __sa_handler.sa_sigaction

extern sigset_t __sigset_all;
extern sigset_t __sigset_app;

#endif  /* __BITS_SIGNAL_H */
