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
#ifndef __BITS_TYPES_H
#define __BITS_TYPES_H 1


#include <bits/cdefs.h>
#include <stddef.h>

#ifndef _NO_STATIC_ASSERT
_Static_assert(sizeof(void *) == sizeof(size_t), "Unsupported, pointer and size_t must have the same size");
#endif

// #include <bits/typesizes.h>

typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

/* Datatypes integer size */
#ifndef __INT8_TYPE__

#define __CHAR16_TYPE__ signed short
#define __CHAR32_TYPE__ signed int
#define __WCHAR_TYPE__ signed int

#if defined __ILP32 || defined __LLP64

#define __INT8_TYPE__ signed char
#define __UINT8_TYPE__ unsigned char
#define __INT16_TYPE__ signed short
#define __UINT16_TYPE__ unsigned short
#define __INT32_TYPE__ signed int
#define __UINT32_TYPE__ unsigned int
#define __INT64_TYPE__ signed long long
#define __UINT64_TYPE__ unsigned long long

#define __INT_LEAST8_TYPE__ signed char
#define __UINT_LEAST8_TYPE__ unsigned char
#define __INT_LEAST16_TYPE__ signed int
#define __UINT_LEAST16_TYPE__ unsigned int
#define __INT_LEAST32_TYPE__ signed int
#define __UINT_LEAST32_TYPE__ unsigned int
#define __INT_LEAST64_TYPE__ signed long long
#define __UINT_LEAST64_TYPE__ unsigned long long

#define __INT_FAST8_TYPE__ signed char
#define __UINT_FAST8_TYPE__ unsigned char
#define __INT_FAST16_TYPE__ signed int
#define __UINT_FAST16_TYPE__ unsigned int
#define __INT_FAST32_TYPE__ signed int
#define __UINT_FAST32_TYPE__ unsigned int
#define __INT_FAST64_TYPE__ signed long long
#define __UINT_FAST64_TYPE__ unsigned long long

#define __INTPTR_TYPE__ signed long
#define __UINTPTR_TYPE__ unsigned long
#define __INTMAX_TYPE__ signed long long
#define __UINTMAX_TYPE__ unsigned long long

#elif defined __LP64

#define __INT8_TYPE__ signed char
#define __UINT8_TYPE__ unsigned char
#define __INT16_TYPE__ signed short
#define __UINT16_TYPE__ unsigned short
#define __INT32_TYPE__ signed int
#define __UINT32_TYPE__ unsigned int
#define __INT64_TYPE__ signed long
#define __UINT64_TYPE__ unsigned long

#define __INT_LEAST8_TYPE__ signed char
#define __UINT_LEAST8_TYPE__ unsigned char
#define __INT_LEAST16_TYPE__ signed int
#define __UINT_LEAST16_TYPE__ unsigned int
#define __INT_LEAST32_TYPE__ signed int
#define __UINT_LEAST32_TYPE__ unsigned int
#define __INT_LEAST64_TYPE__ signed long
#define __UINT_LEAST64_TYPE__ unsigned long

#define __INT_FAST8_TYPE__ signed char
#define __UINT_FAST8_TYPE__ unsigned char
#define __INT_FAST16_TYPE__ signed int
#define __UINT_FAST16_TYPE__ unsigned int
#define __INT_FAST32_TYPE__ signed int
#define __UINT_FAST32_TYPE__ unsigned int
#define __INT_FAST64_TYPE__ signed long
#define __UINT_FAST64_TYPE__ unsigned long

#define __INTPTR_TYPE__ signed long
#define __UINTPTR_TYPE__ unsigned long
#define __INTMAX_TYPE__ signed long
#define __UINTMAX_TYPE__ unsigned long

#else

# error "Undefined architecture"

#endif  /* Datatypes integer size */

#endif /* __INT8_TYPE__ */

typedef __INT8_TYPE__ __int8_t;
typedef __UINT8_TYPE__ __uint8_t;
typedef __INT16_TYPE__ __int16_t;
typedef __UINT16_TYPE__ __uint16_t;
typedef __INT32_TYPE__ __int32_t;
typedef __UINT32_TYPE__ __uint32_t;
typedef __INT64_TYPE__ __int64_t;
typedef __UINT64_TYPE__ __uint64_t;
typedef __INT64_TYPE__ __quad_t;
typedef __UINT64_TYPE__ __u_quad_t;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef int __pid_t;
typedef struct {
    int __val[2];
} __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void *__timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsfilcnt_t;
typedef char *__caddr_t;
typedef unsigned int __socklen_t;
typedef __quad_t *__qaddr_t;


/* Datatypes pointer size */
#if defined __ILP32

typedef long int __fsword_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef int __intptr_t;
typedef long int __ssize_t;

#elif defined __LP64

typedef long int __fsword_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef long int __intptr_t;
typedef long int __ssize_t;

#endif  /* Datatypes pointer size */


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

/* Datatypes 64 */
#if defined __LP64

typedef unsigned long int __ino64_t;
typedef long int __off64_t;
typedef unsigned long int __rlim64_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt64_t;

#else

typedef unsigned long long int __ino64_t;
typedef long long int __off64_t;
typedef unsigned long long int __rlim64_t;
typedef long long int __blkcnt64_t;
typedef unsigned long long int __fsblkcnt64_t;
typedef unsigned long long int __fsfilcnt64_t;

#endif  /* Datatypes 64 */

typedef __off64_t __fpos64_t;
typedef __off64_t __loff_t;


#endif  /* __BITS_TYPES_H */
