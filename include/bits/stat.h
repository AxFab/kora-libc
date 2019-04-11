#ifndef __BITS_STAT_H
#define __BITS_STAT_H 1

#include <bits/types.h>

struct stat
{
    __dev_t st_dev;
    __ino_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;
    __uid_t st_uid;
    __gid_t st_gid;
    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    __time_t st_atime;
    __syscall_ulong_t st_atimensec;
    __time_t st_mtime;
    __syscall_ulong_t st_mtimensec;
    __time_t st_ctime;
    __syscall_ulong_t st_ctimensec;
    __syscall_slong_t __glibc_reserved[3];
};

#endif  /* __BITS_STAT_H */
