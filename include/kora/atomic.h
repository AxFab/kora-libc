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
#ifndef __KORA_ATOMIC_H
#define __KORA_ATOMIC_H 1

#include <bits/cdefs.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t atomic_i8;
typedef int16_t atomic_i16;
typedef int32_t atomic_i32;
typedef int64_t atomic_i64;
typedef void * atomic_ptr;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

static inline void __atomic_inc_1(atomic_i8 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock incb %0" : "=m"(*ref));
}

static inline void __atomic_dec_1(atomic_i8 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock decb %0" : "=m"(*ref));
}

static inline int8_t __atomic_fetch_add_1(atomic_i8 *ref, int8_t val, int mode)
{
    ((void)mode);
    asm volatile("lock xaddb %%al, %2;"
                 :"=a"(val) :"a"(val), "m"(*ref) :"memory");
    return val;
}

static inline int8_t __atomic_fetch_sub_1(atomic_i8 *ref, int8_t val, int mode)
{
    return __atomic_fetch_add_1(ref, -val, mode);
}

bool __atomic_exchange_1(atomic_i8 *ref, int8_t val, int mode);
bool __atomic_compare_exchange_1(atomic_i8 *ref, int8_t *ptr, int8_t val,
    bool weak, int mode_success, int mode_failure);
// {
//     ((void)weak);
//     ((void)mode_success);
//     ((void)mode_failure);
//     int prev = *ptr;
//     asm volatile("cmpxchgb  %1, %2;"
//                  :"=a"(val) :"r"(val), "m"(*ref), "a"(prev) :"memory");
//     *ptr = val;
//     return val == prev;
// }


/* ------------------------------------------------------------------------ */

static inline void __atomic_inc_2(atomic_i16 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock incw %0" : "=m"(*ref));
}

static inline void __atomic_dec_2(atomic_i16 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock decw %0" : "=m"(*ref));
}

static inline int16_t __atomic_fetch_add_2(atomic_i16 *ref, int16_t val, int mode)
{
    ((void)mode);
    asm volatile("lock xaddw %%ax, %2;"
                 :"=a"(val) :"a"(val), "m"(*ref) :"memory");
    return val;
}

static inline int16_t __atomic_fetch_sub_2(atomic_i16 *ref, int16_t val, int mode)
{
    return __atomic_fetch_add_2(ref, -val, mode);
}


int16_t __atomic_exchange_2(atomic_i16 *ref, int16_t val, int mode);
bool __atomic_compare_exchange_2(atomic_i16 *ref, int16_t *ptr, int16_t val,
    bool weak, int mode_success, int mode_failure);
// {
//     ((void)weak);
//     ((void)mode_success);
//     ((void)mode_failure);
//     int prev = *ptr;
//     asm volatile("cmpxchgq  %1, %2;"
//                  :"=a"(val) :"r"(val), "m"(*ref), "a"(prev) :"memory");
//     *ptr = val;
//     return val == prev;
// }

/* ------------------------------------------------------------------------ */

static inline void __atomic_inc_4(atomic_i32 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock incl %0" : "=m"(*ref));
}

static inline void __atomic_dec_4(atomic_i32 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock decl %0" : "=m"(*ref));
}

static inline int32_t __atomic_fetch_add_4(atomic_i32 *ref, int32_t val, int mode)
{
    ((void)mode);
    asm volatile("lock xaddl %%eax, %2;"
                 :"=a"(val) :"a"(val), "m"(*ref) :"memory");
    return val;
}

static inline int32_t __atomic_fetch_sub_4(atomic_i32 *ref, int32_t val, int mode)
{
    return __atomic_fetch_add_4(ref, -val, mode);
}

static inline int32_t __atomic_exchange_4(atomic_i32 *ref, int32_t val, int mode)
{
    ((void)mode);
    register int32_t store = val;
    asm volatile("lock xchg %1, %0" : "=m"(*ref), "=r"(store) : "1"(val));
    return store;
}

static inline bool __atomic_compare_exchange_4(atomic_i32 *ref, int32_t *ptr,
    int32_t val, bool weak, int mode_success, int mode_failure)
{
    ((void)weak);
    ((void)mode_success);
    ((void)mode_failure);
    register int32_t store = *ptr;
    asm volatile("cmpxchg %1, %2;"
                 :"=a"(val) :"r"(val), "m"(*ref), "a"(store) :"memory");
    *ptr = val;
    return val == store;
}

/* ------------------------------------------------------------------------ */
#if 0
static inline void __atomic_inc_8(atomic_i64 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock incq %0" : "=m"(*ref));
}

static inline void __atomic_dec_8(atomic_i64 *ref, int mode)
{
    ((void)mode);
    asm volatile("lock decq %0" : "=m"(*ref));
}

static inline int64_t __atomic_fetch_add_8(atomic_i64 *ref, int64_t val, int mode)
{
    ((void)mode);
    asm volatile("lock xaddq %%rax, %2;"
                 :"=a"(val) :"a"(val), "m"(*ref) :"memory");
    return val;
}

static inline int64_t __atomic_fetch_sub_8(atomic_i64 *ref, int64_t val, int mode)
{
    return __atomic_fetch_add_8(ref, -val, mode);
}


bool __atomic_exchange_8(atomic_i64 *ref, int64_t val, int mode);
bool __atomic_compare_exchange_8(atomic_i64 *ref, int64_t *ptr, int64_t val,
    bool weak, int mode_success, int mode_failure);
#endif
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


#if 0 // defined __C11

#include <stdatomic.h> ?

#else

typedef atomic_i32 atomic_int;
typedef atomic_i32 atomic_intptr_t;

void atomic_store(atomic_int *ptr, int value);
int atomic_load(atomic_int *ptr);

void atomic_dec(atomic_int *ptr);
void atomic_inc(atomic_int *ptr);

int atomic_fetch_add(atomic_int *ptr, int value);
int atomic_fetch_sub(atomic_int *ptr, int value);

int atomic_exchange_explicit(atomic_int *ptr, int value);
bool atomic_compare_exchange_explicit(atomic_int *ref, atomic_int *ptr, int value);


#define atomic_store(p,v) do { (*(p) = (v)); } while(0)
#define atomic_load(p)  (*(p))

#define atomic_inc(p)  __atomic_inc_4(p,0)
#define atomic_dec(p)  __atomic_dec_4(p,0)

#define atomic_fetch_add(p,v)  __atomic_fetch_add_4(p,v,0)
#define atomic_fetch_sub(p,v)  __atomic_fetch_sub_4(p,v,0)

#define atomic_exchange_explicit(r,v)  __atomic_exchange_4(r,v,0)
#define atomic_compare_exchange_explicit(r,p,v)  \
    __atomic_compare_exchange_4(r,p,v,false,0,0)

#define atomic_ptr_compare_exchange(r,p,v) \
    __atomic_compare_exchange_4((atomic_i32*)(r),p,(int32_t)(v),false,0,0)

#endif // defined __C11


#define atomic_exchange atomic_exchange_explicit
#define atomic_compare_exchange atomic_compare_exchange_explicit


#endif  /* __KORA_ATOMIC_H */
