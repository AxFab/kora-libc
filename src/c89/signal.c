#include <signal.h>
#include <unistd.h>

sigset_t __sigset_all = ~0ULL;
sigset_t __sigset_app = ~0ULL;

sighandler_t signal(int signum, sighandler_t handler)
{
    struct sigaction sa_old;
    struct sigaction sa = {
        .sa_handler = handler,
        // .sa_flags = SA_RESTART,
    };

    if (sigaction(signum, &sa, &sa_old) < 0)
        return SIG_ERR;
    return sa_old.sa_handler;
}

int raise(int signum)
{
    sigset_t set;
    sigprocmask(SIG_BLOCK, &__sigset_app, &set);
    int ret = kill(getpid(), signum);
    sigprocmask(SIG_SETMASK, &set, NULL);
    return ret;
}

