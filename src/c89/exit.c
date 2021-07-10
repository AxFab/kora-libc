#include <bits/atomic.h>
#include <signal.h>
#include <malloc.h>

_Noreturn void _Exit(int code);

struct func_list {
    struct func_list *next;
    void (*fs[32])();
    int count;
};

struct func_list __atexit_builtin, *__atexit_head;
struct func_list __at_quick_exit_head;

static atomic_int __atexit_lock = 0;
static atomic_int __at_quick_exit_lock = 0;
static atomic_int __abort_lock = 0;


static void __run_funcs(struct func_list *head, atomic_int *lock)
{
    void (*func)(void);
    while (head->count-- > 0) {
        func = head->fs[head->count];
        __unlock(lock);
        func();
        __lock(lock);
    }
}

static void __run_atexit()
{
    __lock(&__atexit_lock);
    for (; __atexit_head; __atexit_head = __atexit_head->next)
        __run_funcs(__atexit_head, &__atexit_lock);
    __unlock(&__atexit_lock);
}

static void __run_at_quick_exit()
{
    __lock(&__at_quick_exit_lock);
    __run_funcs(&__at_quick_exit_head, &__at_quick_exit_lock);
    __unlock(&__at_quick_exit_lock);
}

int atexit(void (*func)(void))
{
    __lock(&__atexit_lock);

    if (!__atexit_head)
        __atexit_head = &__atexit_builtin;

    if (__atexit_head->count == 32) {
        struct func_list *fl = calloc(sizeof(struct func_list), 1);
        if (fl == NULL) {
            __unlock(&__atexit_lock);
            return -1;
        }
        fl->next = __atexit_head;
        __atexit_head = fl;
    }

    __atexit_head->fs[__atexit_head->count] = func;
    __atexit_head->count++;
    __unlock(&__atexit_lock);
    return 0;
}

int at_quick_exit(void (*func)(void))
{
    __lock(&__at_quick_exit_lock);
    if (__at_quick_exit_head.count == 32)
        return -1;

    __at_quick_exit_head.fs[__at_quick_exit_head.count] = func;
    __at_quick_exit_head.count++;
    __unlock(&__at_quick_exit_lock);
    return 0;
}


_Noreturn void abort(void)
{
    // Standard method
    raise(SIGABRT);

    // If we return we need to reset the handler
    sigset_t all = ~0ULL;
    sigprocmask(SIG_BLOCK, &all, NULL);

    __lock(&__abort_lock);
    signal(SIGABRT, SIG_DFL);
    raise(SIGABRT);

    // Something wrong, crash the app
    atomic_crash();
    raise(SIGKILL);
    _Exit(127);
}


_Noreturn void exit(int code)
{
    __run_atexit();
    // __libc_exit_fini();
    // __stdio_exit();
    _Exit(code);
}


_Noreturn void quick_exit(int code)
{
    __run_at_quick_exit();
    _Exit(code);
}

