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
#ifndef __SYS_TYPES_H
#define __SYS_TYPES_H 1

#include <bits/types.h>

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;


typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;



typedef __dev_t dev_t;
typedef __uid_t uid_t;
typedef __gid_t gid_t;
typedef __ino_t ino_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __off_t off_t;
typedef __pid_t pid_t;
typedef __fsid_t fsid_t;
// typedef __clock_t clock_t;
typedef __rlim_t rlim_t;
typedef __id_t id_t;
// typedef __time_t time_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef __daddr_t daddr_t;
typedef __key_t key_t;
// typedef __clockid_t clockid_t;
// typedef __timer_t timer_t;
typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef __caddr_t caddr_t;
typedef __socklen_t socklen_t;
typedef __qaddr_t qaddr_t;


typedef __fsword_t fsword_t;
typedef __syscall_slong_t syscall_slong_t;
typedef __syscall_ulong_t syscall_ulong_t;
typedef __ssize_t ssize_t;


typedef __ino64_t ino64_t;
typedef __off64_t off64_t;
typedef __rlim64_t rlim64_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef __loff_t loff_t;



#endif  /* __SYS_TYPES_H */
