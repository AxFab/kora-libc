/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
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
#ifndef __UNISTD_H
#define __UNISTD_H 1

#include <stddef.h>
#include <bits/cdefs.h>
#include <bits/types.h>

#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1

int pipe(int [2]);
int pipe2(int [2], int);
int close(int);
int posix_close(int, int);
int dup(int);
int dup2(int, int);
int dup3(int, int, int);
__off_t lseek(int, __off_t, int);
int fsync(int);
int fdatasync(int);

__ssize_t read(int, void *, size_t);
__ssize_t write(int, const void *, size_t);
__ssize_t pread(int, void *, size_t, __off_t);
__ssize_t pwrite(int, const void *, size_t, __off_t);

int chown(const char *, __uid_t, __gid_t);
int fchown(int, __uid_t, __gid_t);
int lchown(const char *, __uid_t, __gid_t);
int fchownat(int, const char *, __uid_t, __gid_t, int);

int link(const char *, const char *);
int linkat(int, const char *, int, const char *, int);
int symlink(const char *, const char *);
int symlinkat(const char *, int, const char *);
__ssize_t readlink(const char *restrict, char *restrict, size_t);
__ssize_t readlinkat(int, const char *restrict, char *restrict, size_t);
int unlink(const char *);
int unlinkat(int, const char *, int);
int rmdir(const char *);
int truncate(const char *, __off_t);
int ftruncate(int, __off_t);


int access(const char *, int);
int faccessat(int, const char *, int, int);

int chdir(const char *);
int fchdir(int);
char *getcwd(char *, size_t);

unsigned alarm(unsigned);
unsigned sleep(unsigned);
int pause(void);

__pid_t fork(void);
int execve(const char *, char *const [], char *const []);
int execv(const char *, char *const []);
int execle(const char *, const char *, ...);
int execl(const char *, const char *, ...);
int execvp(const char *, char *const []);
int execlp(const char *, const char *, ...);
int fexecve(int, char *const [], char *const []);
_Noreturn void _exit(int);

__pid_t getpid(void);
__pid_t getppid(void);
__pid_t getpgrp(void);
__pid_t getpgid(__pid_t);
int setpgid(__pid_t, __pid_t);
__pid_t setsid(void);
__pid_t getsid(__pid_t);
char *ttyname(int);
int ttyname_r(int, char *, size_t);
int isatty(int);
__pid_t tcgetpgrp(int);
int tcsetpgrp(int, __pid_t);

__uid_t getuid(void);
__uid_t geteuid(void);
__gid_t getgid(void);
__gid_t getegid(void);
int getgroups(int, __gid_t []);
int setuid(__uid_t);
int seteuid(__uid_t);
int setgid(__gid_t);
int setegid(__gid_t);

char *getlogin(void);
int getlogin_r(char *, size_t);
int gethostname(char *, size_t);
char *ctermid(char *);




#endif  /* __UNISTD_H */
