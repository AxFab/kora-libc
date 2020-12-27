#ifndef __BITS_STAT_H
#define __BITS_STAT_H 1

#include <bits/types.h>



/* Encoding of the file mode.  */

#define S_IFMT    0170000 /* These bits determine file type.  */

/* File types.  */
#define S_IFDIR   0040000 /* Directory.  */
#define S_IFCHR   0020000 /* Character device.  */
#define S_IFBLK   0060000 /* Block device.  */
#define S_IFREG   0100000 /* Regular file.  */
#define S_IFIFO   0010000 /* FIFO.  */
#define S_IFLNK   0120000 /* Symbolic link.  */
#define S_IFSOCK  0140000 /* Socket.  */

/* Protection bits.  */
#define S_ISUID   04000   /* Set user ID on execution.  */
#define S_ISGID   02000   /* Set group ID on execution.  */
#define S_ISVTX   01000   /* Save swapped text after use (sticky).  */
#define S_IREAD   0400    /* Read by owner.  */
#define S_IWRITE  0200    /* Write by owner.  */
#define S_IEXEC   0100    /* Execute by owner.  */

#ifdef __USE_ATFILE
# define UTIME_NOW  ((1l << 30) - 1l)
# define UTIME_OMIT ((1l << 30) - 2l)
#endif


#define S_ISDIR(m)   (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)   (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)   (((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m)   (((m) & S_IFMT) == S_IFREG)
#define S_ISFIFO(m)   (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m)   (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m)   (((m) & S_IFMT) == S_IFSOCK)


struct stat {
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
