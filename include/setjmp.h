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
#ifndef __SETJMP_H
#define __SETJMP_H 1

#include <bits/cdefs.h>
#include <bits/setjmp.h>

__STDC_GUARD

typedef struct __jmp_buf_ex {
    __jmp_buf __jb;
    unsigned long __fl;
    unsigned long __ss[128/sizeof(long)];
} jmp_buf[1];


#define setjmp setjmp
int setjmp (jmp_buf);
_Noreturn void longjmp (jmp_buf, int);


#if defined __UNIX
int _setjmp (jmp_buf);
_Noreturn void _longjmp (jmp_buf, int);
#endif


#if defined __POSIX || defined __UNIX
typedef jmp_buf sigjmp_buf;
int sigsetjmp (sigjmp_buf, int);
_Noreturn void siglongjmp (sigjmp_buf, int);
#endif


__STDC_END

#endif  /* __SETJMP_H */
