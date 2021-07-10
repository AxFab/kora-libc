#include <sys/mman.h>
#include <sys/syscall.h>
#include <errno.h>
#include "syscallno.h"

struct mmap {
    unsigned long addr;
    unsigned long len;
    unsigned long prot;
    unsigned long flags;
    unsigned long fd;
    unsigned long offset;

    // void *addr;
    // size_t length;
    // int protection;
    // int flags;
    // int fd;
    // __off_t off;
};

void *mmap(void *addr, size_t length, int prot, int flags, int fd, __off_t off)
{
    long ret;
    // if (off & OFF_MASK) {
    //     errno = EINVAL;
    //     return MAP_FAILED;
    // }
    // if (len >= PTRDIFF_MAX) {
    //     errno = ENOMEM;
    //     return MAP_FAILED;
    // }

    struct mmap args;
    args.addr = (size_t)addr;
    args.len = length;
    args.prot = prot;
    args.flags = flags;
    args.fd = fd;
    args.offset = off;

    ret = syscall(SYS_old_mmap, &args);
    // #ifdef SYS_mmap2
    //     ret = syscall(SYS_mmap, addr, length, prot, flags, fd, (__size_t)off);
    // #else
    //     ret = syscall(SYS_mmap, addr, length, prot, flags, fd, (__size_t)off);
    // #endif
    /* Fixup incorrect EPERM from kernel. */
    // if (ret == -EPERM && !start && (flags&MAP_ANON) && !(flags&MAP_FIXED))
    // ret = -ENOMEM;

    return (void *)ret;
}

int munmap(void *addr, size_t length)
{
    return syscall(SYS_munmap, addr, length);
}

// int mprotect(void *addr, size_t length, int prot)
// int msync(void *addr, size_t length, int flags);

// int mlock(const void *addr, size_t length);
// int munlock(const void *addr, size_t length);
// int mlockall(int);
// int munlockall(void);

