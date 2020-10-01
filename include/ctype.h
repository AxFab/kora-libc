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
#ifndef __CTYPE_H
#define __CTYPE_H 1


#include <bits/cdefs.h>


__STDC_GUARD

enum {
    _ISupper = 0x001,
    _ISlower = 0x002,
    _ISalpha = 0x004,
    _ISdigit = 0x008,
    _ISxdigit = 0x010,
    _ISspace = 0x020,
    _ISprint = 0x040,
    _ISgraph = 0x080,
    _ISblank = 0x100,
    _IScntrl = 0x200,
    _ISpunct = 0x400,
    _ISalnum = 0x800,
};

unsigned short int __ctype_b(int);
int __ctype_tolower(int);
int __ctype_toupper(int);


int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int islower(int c);
int isgraph(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int isblank(int c);

int tolower(int c);
int toupper(int c);

int isascii(int c);
int toascii(int c);


#if __LOCALE

#include <bits/locale.h>

int isalnum_l(int c, __locale_t l);
int isalpha_l(int c, __locale_t l);
int iscntrl_l(int c, __locale_t l);
int isdigit_l(int c, __locale_t l);
int islower_l(int c, __locale_t l);
int isgraph_l(int c, __locale_t l);
int isprint_l(int c, __locale_t l);
int ispunct_l(int c, __locale_t l);
int isspace_l(int c, __locale_t l);
int isupper_l(int c, __locale_t l);
int isxdigit_l(int c, __locale_t l);
int isblank_l(int c, __locale_t l);

int tolower_l(int c, __locale_t l);
int toupper_l(int c, __locale_t l);

#endif

#if !defined __cplusplus && !defined _NO_CTYPE_MACRO

#define isalnum(c)  (_ISalnum & __ctype_b(c))
#define isalpha(c)  (_ISalpha & __ctype_b(c))
#define iscntrl(c)  (_IScntrl & __ctype_b(c))
#define isdigit(c)  (_ISdigit & __ctype_b(c))
#define islower(c)  (_ISlower & __ctype_b(c))
#define isgraph(c)  (_ISgraph & __ctype_b(c))
#define isprint(c)  (_ISprint & __ctype_b(c))
#define ispunct(c)  (_ISpunct & __ctype_b(c))
#define isspace(c)  (_ISspace & __ctype_b(c))
#define isupper(c)  (_ISupper & __ctype_b(c))
#define isxdigit(c)  (_ISxdigit & __ctype_b(c))
#define isblank(c)  (_ISblank & __ctype_b(c))

#define isascii(c)  ((unsigned)(c) < 128)

#endif

__STDC_END

#endif  /* __CTYPE_H */
