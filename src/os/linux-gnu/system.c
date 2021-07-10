#include <bits/cdefs.h>
#include <sys/syscall.h>
#include "syscallno.h"

_Noreturn void _Exit(int status)
{
#ifdef SYS_exit_group
    syscall(SYS_exit_group, status);
#endif
    for (;;)
        syscall(SYS_exit, status);
}




