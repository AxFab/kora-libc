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
#include <stdlib.h>
#include "../c89/allocator.h"
#include "check.h"
#include <sys/mman.h>
#include <errno.h>

START_TEST(test_alloc)
{
    void *base = _valloc(0x400000);
    ck_ok(base != NULL);
    memset(base, 0, 0x400000);
    void *limit = ((char*)base) + 0x400000;
    ck_ok(limit > base);

    heap_arena_t arena;
    setup_arena(&arena, (size_t)base, 0x400000, 16 * _Kib_, HEAP_CHECK | HEAP_PARANO);

    void *p0 = malloc_r(&arena, 163);
    ck_ok(p0 > base && p0 < limit);

    void *p1 = malloc_r(&arena, 16);
    ck_ok(p1 > base && p1 < limit);

    void *p2 = malloc_r(&arena, 48);
    ck_ok(p2 > base && p2 < limit);

    void *p3 = malloc_r(&arena, 72);
    ck_ok(p3 > base && p3 < limit);

    free_r (&arena, p2);
    void *p4 = malloc_r(&arena, 8);
    ck_ok(p4 > base && p4 < limit);
    ck_ok(p4 == p2);

    void *p5 = malloc_r(&arena, 32);
    ck_ok(p5 > base && p5 < limit);

    munmap(base, 0x400000);
}
END_TEST()


START_TEST(test_alloc_rep)
{
    void *base = _valloc(0x400000);
    ck_ok(base != NULL);
    memset(base, 0, 0x400000);
    void *limit = ((char*)base) + 0x400000;
    ck_ok(limit > base);

    heap_arena_t arena;
    setup_arena(&arena, (size_t)base, 0x400000, 16 * _Kib_, HEAP_CHECK | HEAP_PARANO);

    void *p0 = malloc_r(&arena, 72);
    ck_ok(p0 > base && p0 < limit);

    void *p1 = malloc_r(&arena, 36);
    ck_ok(p1 > base && p1 < limit);

    void *p2 = malloc_r(&arena, 208);
    ck_ok(p2 > base && p2 < limit);

    void *p3 = malloc_r(&arena, 56);
    ck_ok(p3 > base && p3 < limit);

    void *p4 = malloc_r(&arena, 512);
    ck_ok(p4 > base && p4 < limit);

    void *p5 = malloc_r(&arena, 4);
    ck_ok(p5 > base && p5 < limit);

    void *p6 = malloc_r(&arena, 8);
    ck_ok(p6 > base && p6 < limit);
    free_r (&arena, p6);

    free_r(&arena, p4);
    for (int i = 0; i < 8196; ++i) {
        void *p7 = malloc_r(&arena, 16);
        ck_ok(p7 > base && p7 < limit);
        ck_ok(p7 == p4);
        free_r(&arena, p7);
    }

    munmap(base, 0x400000);
}
END_TEST()

void ck_heap(Suite *s)
{
    ck_test_case(s, test_alloc);
    ck_test_case(s, test_alloc_rep);
}
