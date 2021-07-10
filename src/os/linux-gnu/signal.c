#include <signal.h>
#include <sys/syscall.h>
#include "syscallno.h"

int kill(__pid_t pid, int sig)
{
    return syscall(SYS_kill, pid, sig);
}


int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
#ifdef SYS_rt_sigprocmask
    return syscall(SYS_rt_sigprocmask, how, set, old, sizeof(sigset_t));
#else
    return syscall(SYS_sigprocmask, how, set, old);
#endif
}


int sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
    return syscall(SYS_sigaction, sig, sa, old);
}

