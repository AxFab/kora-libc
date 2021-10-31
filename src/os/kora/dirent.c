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
#include <dirent.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/syscall.h>

int close(int fd);

struct __dirstream {
    int fd;
    int pos;
    int len;
    int cur;
    int cap;
    int lock;
    char buf[0];
};

#define DIRSTREAM_BUF_SIZE sizeof(struct dirent)


int dirfd(DIR *dir)
{
    return dir->fd;
}

DIR *fdopendir_(int fd)
{
    DIR *dir = malloc(sizeof(*dir) + DIRSTREAM_BUF_SIZE);
    dir->fd = fd;
    dir->pos = DIRSTREAM_BUF_SIZE;
    dir->len = DIRSTREAM_BUF_SIZE;
    dir->len = DIRSTREAM_BUF_SIZE;
    return dir;
}

DIR *fdopendir(int fd)
{
    // TODO -- Check this is a directory
    return fdopendir_(fd);
}

DIR *opendir(const char *name)
{
    int fd = open(name, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (fd < 0)
        return 0;
    return fdopendir_(fd);
}

int closedir(DIR *dir)
{
    int ret = close(dir->fd);
    free(dir);
    return ret;
}

int readdir_r(DIR *dir, struct dirent *entry, struct dirent **restrict result)
{
    if (dir->pos >= dir->len) {
        int len = syscall(SYS_READDIR, dir->fd, dir->buf, DIRSTREAM_BUF_SIZE);
        if (len < 0)
            return 0;
        dir->pos = 0;
        dir->len = len;
    }
    if (dir->len == 0) {
        if (result)
            *result = NULL;
        return NULL;
    }
    memcpy(entry, (void *)(dir->buf + dir->pos), sizeof(struct dirent));
    dir->pos += entry->d_reclen;
    dir->cur = entry->d_off;
    if (result)
        *result = entry;
    return entry;
}

struct dirent *readdir(DIR *dir)
{
    struct dirent *entry;
    if (dir->pos >= dir->len) {
        int len = syscall(SYS_READDIR, dir->fd, dir->buf, DIRSTREAM_BUF_SIZE);
        if (len < 0)
            return 0;
        dir->pos = 0;
        dir->len = len;
    }
    if (dir->len == 0)
        return NULL;
    entry = (void *)(dir->buf + dir->pos);
    dir->pos += entry->d_reclen;
    dir->cur = entry->d_off;
    return entry;
}

void rewinddir(DIR *dir);

long telldir(DIR *dir)
{
    return dir->cur;
}
