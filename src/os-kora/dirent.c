#include <dirent.h>
#include <fcntl.h>
#include <kora/syscalls.h>

struct __dirstream {
    int fd;
    int pos;
    int len;
    int cur;
    char buf[0];
};

#define DIRSTREAM_BUF_SIZE 2048


int dirfd(DIR *dir)
{
    return dir->fd;
}

DIR *fdopendir(int fd)
{
    DIR *dir = malloc(sizeof(*dir) + DIRSTREAM_BUF_SIZE);
    dir->fd = fd;
    dir->pos = DIRSTREAM_BUF_SIZE;
    dir->len = DIRSTREAM_BUF_SIZE;
    return dir;
}

DIR *opendir(const char *name)
{
    int fd = open(name, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (fd < 0)
        return 0;
    return fdopendir(fd);
}

int closedir(DIR *dir)
{
    int ret = close(dir->fd);
    free(dir);
    return ret;
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
    entry = (void*)(dir->buf + dir->pos);
    dir->pos += entry->d_reclen;
    dir->cur = entry->d_off;
    return entry;
}
