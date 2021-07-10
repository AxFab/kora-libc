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
#if !defined __LIMITS_H
# error "Never use <bits/limits_sys.h> directly; include <limits.h> instead."
#endif


#define PIPE_BUF 4096
#define FILESIZEBITS 64
#define NAME_MAX 255
#define PATH_MAX 4096
#define NGROUPS_MAX 32
#define ARG_MAX 131072
#define IOV_MAX 1024
#define SYMLOOP_MAX 40
#define WORD_BIT 32
#define TZNAME_MAX 6
#define TTY_NAME_MAX 32
#define HOST_NAME_MAX 255

#define PTHREAD_KEYS_MAX 128
#define PTHREAD_STACK_MIN 2048
#define PTHREAD_DESTRUCTOR_ITERATIONS 4
#define SEM_VALUE_MAX 0x7fffffff
#define SEM_NSEMS_MAX 256
#define DELAYTIMER_MAX 0x7fffffff
#define MQ_PRIO_MAX 32768
#define LOGIN_NAME_MAX 256
