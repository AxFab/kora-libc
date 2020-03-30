#ifndef __FCNTL_H
#define __FCNTL_H 1

#include <bits/cdefs.h>
#if !defined __UNIX && !defined __POSIX
#error "The header <fcntl.h> requires unix or posix support."
#endif


#include <bits/stat.h>
#include <bits/libio.h>
#include <bits/timespec.h>

struct flock {
    short int l_type;
    short int l_whence;
    __off_t l_start;
    __off_t l_len;
    __pid_t l_pid;
};

typedef __mode_t mode_t;
typedef __off_t off_t;
typedef __pid_t pid_t;


int fcntl(int fd, int cmd, ...);
int open(const char *file, int oflag, ...);
int openat(int fd, const char *file, int oflag, ...);
int creat(const char *file, mode_t mode);
int lockf(int fd, int cmd, off_t len);
int posix_fadvise(int fd, off_t offset, off_t len, int advise);
int posix_fallocate(int fd, off_t offset, off_t len);

#endif  /* __FCNTL_H */
