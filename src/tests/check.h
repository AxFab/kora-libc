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

static inline void ck_test_case_(Suite *s, void (*func)(int), const char *name)
{
    struct ck_test *ts = malloc(sizeof(struct ck_test));
    ts->func = func;
    ts->next = s->tail;
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
    fprintf(stderr, "Start unit-tests process: \e[33m%d\e[0m tests\n", s->count);
    for (int i = 0; s->cursor; ++i) {
        struct ck_test *ts = s->cursor;
        s->cursor = ts->next;
        int r = setjmp(s->jmpbuf);
        if (r == 0) {
            s->cases++;
            ts->func(i);
            fprintf(stderr, "  - Test %-32s  [ \e[32mOK\e[0m ]\n", ts->name);
            s->success++;
        } else {
            fprintf(stderr, "  - Test %-32s  [\e[31mFAILS\e[0m]\n", ts->name);
            s->fails++;
        }
    }
    if (s->fails == 0)
        fprintf(stderr, "Run successfully  %d success, %d cases\n", s->success, s->cases);
    else
        fprintf(stderr, "Run success at %d%%, %d fails, %d success, %d cases\n", s->success * 100 / s->cases, s->fails, s->success, s->cases);
    return s->fails;
}


#endif  /* __CHECK_H */
