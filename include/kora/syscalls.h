/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2019  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#ifndef _KORA_SYSCALLS_H
#define _KORA_SYSCALLS_H 1

#include <stddef.h>
#include <stdint.h>

#include <bits/xtime.h>
#include <bits/types.h>

typedef int64_t xoff_t;

struct dirent {
    int d_ino;
    int d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];
};

struct filemeta {
    int ino;
    int dev;
    int block;
    int ftype;

    int64_t size;
    int64_t rsize;

    uint64_t ctime;
    uint64_t mtime;
    uint64_t atime;
    uint64_t btime;
};

enum sys_vars {
    SNFO_NONE = 0,
    SNFO_ARCH,
    SNFO_SNAME,
    SNFO_OSNAME,
    SNFO_PWD,
    // SNFO_ARCH
    // SNFO_GITH
    // SNFO_SNAME
    // SNFO_VERSION
    // SNFO_RELEASE
    // SNFO_OSNAME
    // SNFO_HOSTNAME
    // SNFO_DOMAIN
    // SNFO_USER
    // SNFO_USERNAME
    // SNFO_USERMAIL
    // SNFO_PWD
};

enum syscall_no {
    SYS_EXIT = 0,
    SYS_SLEEP,

    SYS_FUTEX_WAIT,
    SYS_FUTEX_REQUEUE,
    SYS_FUTEX_WAKE,

    SYS_SPAWN,
    SYS_THREAD,

    SYS_MMAP,
    SYS_MUNMAP,
    SYS_MPROTECT,

    SYS_GINFO, // 10
    SYS_SINFO,

    SYS_OPEN,
    SYS_CREATE,
    SYS_CLOSE,
    SYS_OPENDIR,
    SYS_READDIR,
    SYS_SEEK,
    SYS_READ, // 16
    SYS_WRITE,
    SYS_ACCESS,
    SYS_FCNTL, // 19

    SYS_PIPE,
    SYS_WINDOW,
    SYS_FSTAT,

    SYS_XTIME,
};

// #define SPW_SHUTDOWN 0xcafe
// #define SPW_REBOOT 0xbeca
// #define SPW_SLEEP 0xbabe
// #define SPW_HIBERNATE 0xbeaf
// #define SPW_SESSION 0xdead


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// Tasks, Process

void sys_exit(int code);
// long sys_wait(int pid, int *status, int option);
long sys_sleep(xtime_t *timeout, xtime_t *remain);
long sys_futex_wait(int *addr, int val, xtime_t *timeout, int flags);
long sys_futex_requeue(int *addr, int val, int val2, int *addr2, int flags);
long sys_futex_wake(int *addr, int val);

long sys_spawn(const char *program, const char **args, const char **envs, int *streams, int flags);
long sys_thread(const char *name, void *entry, void *params, size_t len, int flags);

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// Memory
void *sys_mmap(void *addr, size_t length, unsigned flags, int fd, size_t off);
long sys_munmap(void *addr, size_t length);
long sys_mprotect(void *addr, size_t length, unsigned flags);
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

long sys_ginfo(unsigned info, char *buf, size_t len);
long sys_sinfo(unsigned info, const char *buf, size_t len);
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// File system
long sys_open(int dirfd, const char *path, int flags, int mode);
long sys_close(int fd);
long sys_readdir(int fd, char *buf, size_t len);
long sys_seek(int fd, xoff_t offset, int whence);
long sys_read(int fd, char *buf, int len);
long sys_write(int fd, const char *buf, int len);
long sys_access(int dirfd, const char *path, int flags);
long sys_fcntl(int fd, int cmd, void **args);
long sys_fstat(int dirfd, const char *path, struct filemeta *meta, int flags);

// #define SYS_WINDOW  18
// #define SYS_PIPE  19
long sys_pipe(int *fds, int flags);


int sys_xtime(int name, xtime_t *ptime);

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// Signals
// #define SYS_SIGRAISE  15
// #define SYS_SIGACTION  16
// #define SYS_SIGRETURN  17



// #include <kernel/syscalls.h>

// #define SYS_POWER  12
// #define SYS_SCALL  13
// #define SYS_SYSLOG  14
// #define SYS_GINFO  25
// #define SYS_SINFO  26

// #define SYS_YIELD  0
// #define SYS_EXIT  1
// #define SYS_WAIT  2
// #define SYS_EXEC  11
// #define SYS_CLONE  21

// #define SYS_SIGRAISE  15
// #define SYS_SIGACTION  16
// #define SYS_SIGRETURN  17

// #define SYS_MMAP  3
// #define SYS_MUNMAP  4
// #define SYS_MPROTECT  5

// #define SYS_ACCESS 33
// #define SYS_OPEN  6
// #define SYS_CLOSE  7
// #define SYS_READ  8
// #define SYS_WRITE  9
// #define SYS_SEEK  10
// #define SYS_READDIR  33

// #define SYS_WINDOW  18
// #define SYS_PIPE  19
// #define SYS_FCNTL  20
// #define SYS_FSTAT  24

// #define SYS_FUTEX_WAIT 22
// #define SYS_FUTEX_REQUEUE 23


// #define SYS_START 31
// #define SYS_STOP 32

// #define SYS_SLEEP 30
// #define SYS_SFORK 27
// #define SYS_PFORK 28
// #define SYS_TFORK 29



/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

//struct iovec {
//    char *buffer;
//    size_t length;
//};

// struct image {
//     int width, height, pitch, format;
// };


// struct filemeta {
//     int ino;
//     int dev;
//     int block;
//     int ftype;

//     int64_t size;
//     int64_t rsize;

//     uint64_t ctime;
//     uint64_t mtime;
//     uint64_t atime;
//     uint64_t btime;
// };

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


// /* System */
// int sys_power(unsigned long action, unsigned long delay_us);
// int sys_scall(const char *module);
// int sys_syslog(const char *msg);
// int sys_sysinfo(unsigned long info, char *buf, size_t len);
// /* Task */
// int sys_yield(unsigned long flags);
// long sys_exit(int status);
// void sys_stop(long status, unsigned long type);
// int sys_wait(unsigned long cause, long param, unsigned long timeout_us);
// int sys_exec(const char *exec, char **args, char **env, unsigned long flags);
// int sys_clone(unsigned long flags);
// /* Signals */
// int sys_sigraise(unsigned long signum, long pid);
// int sys_sigaction(unsigned long signum, void *sigaction);
// void sys_sigreturn();
// /* Memory */
// void *sys_mmap(void *addr, size_t length, unsigned flags, int fd, off_t off);
// int sys_munmap(size_t addr, size_t len);
// int sys_mprotect(size_t addr, size_t len, unsigned int flags);
// /* Stream */
// int sys_open(int fd, const char *path, unsigned long flags, unsigned long mode);
// int sys_close(int fd);
// int sys_read(int fd, const struct iovec *iovec, unsigned long count);
// int sys_write(int fd, const struct iovec *iovec, unsigned long count);
// int sys_seek(int fd, off_t off, unsigned long whence);
// /* - */
// int sys_window(int ctx, int width, int height, unsigned flags);
// int sys_pipe(int *fds);


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */


#endif  /* _KORA_SYSCALLS_H */
