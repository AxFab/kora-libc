
void exit(int);
void printf(const char *, ...);

void __ni(const char *func)
{
    printf("Not Implemented: %s\n", func);
    exit(-1);
}

#define __NI(n) void n() { __ni(#n); }

__NI(waitpid)
__NI(getpid)
__NI(kill)
__NI(sigaction)
__NI(vfwprintf)
__NI(vfscanf)
__NI(pspawn)
__NI(vfwscanf)
__NI(sigprocmask)

