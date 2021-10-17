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
#ifndef __SYS_SYSCALL_H
#define __SYS_SYSCALL_H 1

#include <stddef.h>
#include <bits/syscall.h>

int __syscall0(int no, ...);
int __syscall1(int no, ...);
int __syscall2(int no, ...);
int __syscall3(int no, ...);
int __syscall4(int no, ...);
int __syscall5(int no, ...);
int __syscall6(int no, ...);
int __syscall7(int no, ...);

#define sz(i)   ((size_t)(i))
#define syscall(no,...)                     syscall_x(no, __VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)
#define syscall_x(a,b,c,d,e,f,g,h,i,...)    syscall_ ## i (a,b,c,d,e,f,g,h)
#define syscall_0(a,b,c,d,e,f,g,h)          __syscall0(a)
#define syscall_1(a,b,c,d,e,f,g,h)          __syscall1(a,sz(b))
#define syscall_2(a,b,c,d,e,f,g,h)          __syscall2(a,sz(b),sz(c))
#define syscall_3(a,b,c,d,e,f,g,h)          __syscall3(a,sz(b),sz(c),sz(d))
#define syscall_4(a,b,c,d,e,f,g,h)          __syscall4(a,sz(b),sz(c),sz(d),sz(e))
#define syscall_5(a,b,c,d,e,f,g,h)          __syscall5(a,sz(b),sz(c),sz(d),sz(e),sz(f))
#define syscall_6(a,b,c,d,e,f,g,h)          __syscall6(a,sz(b),sz(c),sz(d),sz(e),sz(f),sz(g))
#define syscall_7(a,b,c,d,e,f,g,h)          __syscall7(a,sz(b),sz(c),sz(d),sz(e),sz(f),sz(g),sz(h))

#endif  /* __SYS_SYSCALL_H */
