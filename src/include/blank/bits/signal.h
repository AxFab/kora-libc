#ifndef __BITS_SIGNAL_H
#define __BITS_SIGNAL_H 1


typedef int sig_atomic_t;
typedef unsigned long sigset_t;
typedef struct siginfo siginfo_t;


typedef void (*sighandler_t)(int);
typedef void (*sigaction_t)(int, siginfo_t *, void *);



struct sigaction {
    union {
        sighandler_t sa_handler;
        sigaction_t sa_sigaction;
    } __sa_handler;
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

#define sa_handler   __sa_handler.sa_handler
#define sa_sigaction __sa_handler.sa_sigaction

extern sigset_t __sigset_all;
extern sigset_t __sigset_app;

#endif  /* __BITS_SIGNAL_H */
