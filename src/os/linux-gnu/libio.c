#include <bits/libio.h>
#include <bits/types.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include "syscallno.h"

int open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    int mode = va_arg(ap, int);
    va_end(ap);
#if defined SYS_openat
    return syscall(SYS_openat, AT_FDCWD, path, flags | O_LARGEFILE, mode);
#else
    return syscall(SYS_open, path, flags | O_LARGEFILE, mode);
#endif
}

int close(int fd)
{
    return syscall(SYS_close, fd);
}

__ssize_t read(int fd, void *buf, size_t len)
{
    return syscall(SYS_read, fd, buf, len);
}

__ssize_t write(int fd, const void *buf, size_t len)
{
    return syscall(SYS_write, fd, buf, len);
}

__off_t lseek(int fd, __off_t off, int whence)
{
#ifdef SYS__llseek
    __off_t result
    int ret = syscall(SYS_llseek, fd, off >> 24, off, &result, whence);
    return ret != 0 ? -1 : result;
#else
    return syscall(SYS_lseek, fd, (__ssize_t)off, whence);
#endif
}

