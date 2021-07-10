
void exit(int);
void printf(const char *, ...);

void __ni(const char *func)
{
    printf("Not Implemented: %s\n", func);
    exit(-1);
}

#define __NI(n) void n() { __ni(#n); }

__NI(__errno_location)
__NI(execve)
__NI(fork)
__NI(getpid)
__NI(lstat)
__NI(remove)
__NI(waitpid)
__NI(xtime_read)

__NI(vfwprintf)
__NI(vfscanf)
__NI(vfwscanf)

// void lstat() {}
// void rename() {}
// void remove() {}

// void wcscoll() {}
// void wcsftime() {}
// void wcsstr() {}
// void wcstok() {}
// void wcsxfrm() {}

