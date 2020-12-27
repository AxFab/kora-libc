#ifndef __UNISTD_H
#define __UNISTD_H 1

#include <bits/cdefs.h>
#if !defined __UNIX && !defined __POSIX
#error "The header <unistd.h> requires unix or posix support."
#endif

#include <bits/types.h>

int pipe(int [2]);
// int pipe2(int [2], int);
int close(int);
// int posix_close(int, int);
// int dup(int);
// int dup2(int, int);
// int dup3(int, int, int);
// off_t lseek(int, off_t, int);
// int fsync(int);
// int fdatasync(int);

__ssize_t read(int, void *, size_t);
__ssize_t write(int, const void *, size_t);
// ssize_t pread(int, void *, size_t, off_t);
// ssize_t pwrite(int, const void *, size_t, off_t);

// int chown(const char *, uid_t, gid_t);
// int fchown(int, uid_t, gid_t);
// int lchown(const char *, uid_t, gid_t);
// int fchownat(int, const char *, uid_t, gid_t, int);

// int link(const char *, const char *);
// int linkat(int, const char *, int, const char *, int);
// int symlink(const char *, const char *);
// int symlinkat(const char *, int, const char *);
// ssize_t readlink(const char *__restrict, char *__restrict, size_t);
// ssize_t readlinkat(int, const char *__restrict, char *__restrict, size_t);
// int unlink(const char *);
// int unlinkat(int, const char *, int);
// int rmdir(const char *);
// int truncate(const char *, off_t);
// int ftruncate(int, off_t);


int access(const char *, int);
// int faccessat(int, const char *, int, int);

// int chdir(const char *);
// int fchdir(int);
// char *getcwd(char *, size_t);

// unsigned alarm(unsigned);
// unsigned sleep(unsigned);
// int pause(void);

// pid_t fork(void);
// int execve(const char *, char *const [], char *const []);
// int execv(const char *, char *const []);
// int execle(const char *, const char *, ...);
// int execl(const char *, const char *, ...);
// int execvp(const char *, char *const []);
// int execlp(const char *, const char *, ...);
// int fexecve(int, char *const [], char *const []);
// _Noreturn void _exit(int);

// pid_t getpid(void);
// pid_t getppid(void);
// pid_t getpgrp(void);
// pid_t getpgid(pid_t);
// int setpgid(pid_t, pid_t);
// pid_t setsid(void);
// pid_t getsid(pid_t);
// char *ttyname(int);
// int ttyname_r(int, char *, size_t);
// int isatty(int);
// pid_t tcgetpgrp(int);
// int tcsetpgrp(int, pid_t);

// uid_t getuid(void);
// uid_t geteuid(void);
// gid_t getgid(void);
// gid_t getegid(void);
// int getgroups(int, gid_t []);
// int setuid(uid_t);
// int seteuid(uid_t);
// int setgid(gid_t);
// int setegid(gid_t);

// char *getlogin(void);
// int getlogin_r(char *, size_t);
// int gethostname(char *, size_t);
// char *ctermid(char *);




#endif  /* __UNISTD_H */
