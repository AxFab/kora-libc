#ifndef __FCNTL_H
#define __FCNTL_H 1

#include <bits/cdefs.h>
// features
#include <bits/stat.h>
// kernel flags

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

// # 120 "/usr/include/time.h" 3 4
struct timespec {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
};


int fcntl(int fd, int cmd, ...);
int open(const char *file, int oflag, ...);
int openat(int fd, const char *file, int oflag, ...);
int creat(const char *file, mode_t mode);
int lockf(int fd, int cmd, off_t len);
int posix_fadvise(int fd, off_t offset, off_t len, int advise);
int posix_fallocate(int fd, off_t offset, off_t len);

#endif  /* __FCNTL_H */
