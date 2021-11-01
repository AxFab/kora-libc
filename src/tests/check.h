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
#ifndef __CHECK_H
#define __CHECK_H 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

#define START_TEST(n) void n(int __n) {
#define END_TEST() }

#define ck_ok(n)  ck_ok_(n, #n, __FILE__, __LINE__)
#define ck_abort(n)  ck_abort_(__FILE__, __LINE__)
#define ck_test_case(s, f)  ck_test_case_(s, f, #f);

typedef struct ck_suite Suite;

struct ck_test {
    void (*func)(int);
    struct ck_test *next;
    const char *name;
};
struct ck_suite {
    struct ck_test *head;
    struct ck_test *tail;
    int count;
    struct ck_test *cursor;
    jmp_buf jmpbuf;
    int fails;
    int errs;
    int success;
    int cases;
};

extern Suite *__ck_suite;

static inline void ck_ok_(bool assert, const char *expr, const char *file, int line)
{
    if (!assert) {
        fprintf(stderr, "Assertion failed at %s:%d -- %s\n", file, line, expr);
        longjmp(__ck_suite->jmpbuf, 1);
    }
}

static inline void ck_abort_(const char *file, int line)
{
    fprintf(stderr, "Abort test at %s:%d\n", file, line);
    longjmp(__ck_suite->jmpbuf, 2);
}

static inline void ck_test_case_(Suite *s, void (*func)(int), const char *name)
{
    struct ck_test *ts = malloc(sizeof(struct ck_test));
    ts->func = func;
    ts->next = NULL;
    ts->name = name;
    s->count++;
    if (s->tail) {
        s->tail->next = ts;
        s->tail = ts;
    } else {
        s->head = ts;
        s->tail = ts;
    }
}

static inline int ck_run(Suite *s)
{
    __ck_suite = s;
    s->fails = 0;
    s->success = 0;
    s->cases = 0;
    s->cursor = s->head;
    fprintf(stderr, "Start unit-tests process: \033[33m%d\033[0m tests\n", s->count);
    for (int i = 0; s->cursor; ++i) {
        struct ck_test *ts = s->cursor;
        s->cursor = ts->next;
        int r = setjmp(s->jmpbuf);
        if (r == 0) {
            s->cases++;
            ts->func(i);
            fprintf(stderr, "  - Test %-32s  [ \033[32mOK\033[0m ]\n", ts->name);
            s->success++;
        } else if (r == 1) {
            fprintf(stderr, "  - Test %-32s  [\033[31mFAILS\033[0m]\n", ts->name);
            s->fails++;
        } else if (r == 2) {
            fprintf(stderr, "  - Test %-32s  [\033[33mERR.\033[0m]\n", ts->name);
            s->errs++;
        }
        free(ts);
    }
    if (s->fails == 0)
        fprintf(stderr, "Run successfully  %d success, %d cases\n", s->success, s->cases);
    else
        fprintf(stderr, "Run success at %d%%, %d fails, %d success, %d cases\n", s->success * 100 / s->cases, s->fails, s->success, s->cases);
    return s->fails;
}


#endif  /* __CHECK_H */
