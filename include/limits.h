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
#ifndef __LIMITS_H
#define __LIMITS_H 1

#include <bits/cdefs.h>
#include <bits/limits_posix.h>
#include <bits/limits_sys.h>

#if '\xff' > 0
#define CHAR_MIN 0
#define CHAR_MAX 255
#else
#define CHAR_MIN (-128)
#define CHAR_MAX 127
#endif



#if WORDSIZE == 32
#define SSIZE_MAX 0x7fffffffL
#else
#define SSIZE_MAX 0x7fffffffffffffffL
#endif

#if LONG_BIT == 32
#define LONG_MAX 0x7fffffffL
#else
#define LONG_MAX 0x7fffffffffffffffL
#endif

#define LLONG_MAX 0x7fffffffffffffffLL



#define CHAR_BIT 8
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define UCHAR_MAX 255
#define SHRT_MIN  (-1-0x7fff)
#define SHRT_MAX  0x7fff
#define USHRT_MAX 0xffff
#define INT_MIN  (-1-0x7fffffff)
#define INT_MAX  0x7fffffff
#define UINT_MAX 0xffffffffU
#define LONG_MIN (-LONG_MAX-1)
#define ULONG_MAX (2UL*LONG_MAX+1)
#define LLONG_MIN (-LLONG_MAX-1)
#define ULLONG_MAX (2ULL*LLONG_MAX+1)



#define NZERO 20



#define MB_LEN_MAX 6

#define PATH_MAX 4096


/* Arbitrary numbers... */
#define BC_BASE_MAX 99
#define BC_DIM_MAX 2048
#define BC_SCALE_MAX 99
#define BC_STRING_MAX 1000
#define CHARCLASS_NAME_MAX 14
#define COLL_WEIGHTS_MAX 2
#define EXPR_NEST_MAX 32
#define LINE_MAX 4096
#define RE_DUP_MAX 255

// Maximum value of digit in calls to the printf() and scanf() functions.
#define NL_ARGMAX 32767
// Maximum number of bytes in a LANG name.
#define NL_LANGMAX 32
// Maximum message number.
#define NL_MSGMAX 32767
// Maximum number of bytes in an N - to - 1 collation mapping.
#define NL_NMAX 16
// Maximum set number.
#define NL_SETMAX 255
// Maximum number of bytes in a message string.
#define NL_TEXTMAX 4096
// Default process priority.


#endif  /* __LIMITS_H */
