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
#include <errno.h>
#include <bits/types.h>
#include <bits/xtime.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

extern char **__environ;
__pid_t waitpid(__pid_t pid, int *status, int options);
__pid_t pspawn(const char *exec, int *fdset, sigset_t *set, const char *const *args, char *const *envs);


int system(const char *cmd)
{
    if (!cmd)
        return 1;

    const char *args[] = {
        "sh", "-c", cmd, 0
    };

    sigset_t set;
    struct sigaction sa = { .sa_handler = SIG_IGN };
    struct sigaction so_int, so_quit;

    // sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, &so_int);
    sigaction(SIGQUIT, &sa, &so_quit);
    // sigaddset(&sa.sa_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sa.sa_mask, &set);

    __pid_t pid = pspawn("/bin/sh", NULL, &set, args, __environ);
    int err = errno;
    int status = -1;
    if (pid > 0)
        while (waitpid(pid, &status, 0) < 0 && errno == EINTR);

    sigaction(SIGINT, &so_int, NULL);
    sigaction(SIGQUIT, &so_quit, NULL);
    sigprocmask(SIG_SETMASK, &set, NULL);

    errno = err;
    return status;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void perror(const char *msg)
{
    FILE *fp = stderr;
    char *errstr = errno != 0 ? strerror(errno) : NULL;

    FLOCK(fp);
    // void *locale = fp->locale;
    // int mode = fp->mode;

    if (msg && *msg) {
        fwrite_unlocked(msg, strlen(msg), 1, fp);
        fwrite_unlocked(": ", 2, 1, fp);
    }
    if (errstr)
        fwrite_unlocked(errstr, strlen(errstr), 1, fp);
    fwrite_unlocked("\n", 1, 1, fp);

    // fp->mode = mode;
    // fp->locale = locale;
    FUNLOCK(fp);
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define MAXTRIES 100
#define L_tmpnam 20

struct stat;
int lstat(const char *restrict path, struct stat *restrict buf);
int remove(const char *path);
int open(const char *filename, int flags, ...);
int close(int fd);
FILE *fdopen(int fd, const char *mode);


char *__randname(char *template, int len)
{
    static const char *characters =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    xtime_t rel = xtime_read(XTIME_CLOCK);
    rel = rel * 65537;
    for (int i = 0; i < len; ++i, rel /= 62)
        template[i] = characters[rel % 62];
    return template;
}


char *tmpnam(char *buf)
{
    static char internal[L_tmpnam];
    char str[] = "/tmp/tmpnam_XXXXXXX";
    for (int try
             = 0; try
                 < MAXTRIES; try
                     ++) {
                    __randname(&str[12], 7);
                    int r = lstat(str, NULL);
                    if (r < 0 && errno == ENOENT)
                        return strcpy(buf ? buf : internal, str);
                }
    return NULL;
}


FILE *tmpfile(void)
{
    char str[] = "/tmp/tmpfile_XXXXXXX";
    for (int try
             = 0; try
                 < MAXTRIES; try
                     ++) {
                    __randname(&str[13], 7);
                    int fd = open(str, O_RDWR | O_CREAT | O_EXCL, 0600);
                    if (fd >= 0) {
                        remove(str);
                        FILE *fp = fdopen(fd, "w+");
                        if (!fp)
                            close(fd);
                        return fp;
                    }
                }
    return NULL;
}
