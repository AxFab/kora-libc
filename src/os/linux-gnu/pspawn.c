#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>

int execve(const char *filename, char *const argv[], char *const envp[]);
_Noreturn void _Exit(int code);


__pid_t pspawn(const char *exec, int *fdset, sigset_t *set, char *const *args, char *const *envs)
{
    __pid_t pid = fork();
    if (pid != 0)
        return pid;

    // Redirect iostream

    // Change signals

    execve(exec, args, envs);
    _Exit(-1);
}
