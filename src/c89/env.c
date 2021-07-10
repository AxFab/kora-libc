#include <stdlib.h>
#include <string.h>
#include <errno.h>

char **__environ;

void __env_rm_add(char *old, char *new)
{
    static char **env_alloced = NULL;
    static size_t env_alloced_n = 0;
    for (size_t i = 0; i < env_alloced_n; i++) {
        if (env_alloced[i] == old) {
            env_alloced[i] = new;
            free(old);
            return;
        } else if (!env_alloced[i] && new) {
            env_alloced[i] = new;
            new = 0;
        }
    }
    if (!new)
        return;
    char **t = realloc(env_alloced, sizeof * t * (env_alloced_n + 1));
    if (!t)
        return;
    (env_alloced = t)[env_alloced_n++] = new;
}

int __putenv(char *s, size_t l, char *r)
{
    size_t i = 0;
    if (__environ) {
        for (char **e = __environ; *e; e++, i++)
            if (!strncmp(s, *e, l + 1)) {
                char *tmp = *e;
                *e = s;
                __env_rm_add(tmp, r);
                return 0;
            }
    }
    static char **oldenv;
    char **newenv;
    if (__environ == oldenv) {
        newenv = realloc(oldenv, sizeof * newenv * (i + 2));
        if (!newenv)  {
            free(r);
            return -1;
        }
    } else {
        newenv = malloc(sizeof * newenv * (i + 2));
        if (!newenv) {
            free(r);
            return -1;
        }
        if (i)
            memcpy(newenv, __environ, sizeof * newenv * i);
        free(oldenv);
    }
    newenv[i] = s;
    newenv[i + 1] = 0;
    __environ = oldenv = newenv;
    if (r)
        __env_rm_add(0, r);
    return 0;
}


int setenv(const char *var, const char *value, int overwrite)
{
    char *s;
    size_t l1, l2;

    if (!var || !(l1 = strchrnul(var, '=') - var) || var[l1]) {
        errno = EINVAL;
        return -1;
    }
    if (!overwrite && getenv(var))
        return 0;

    l2 = strlen(value);
    s = malloc(l1 + l2 + 2);
    if (!s)
        return -1;
    memcpy(s, var, l1);
    s[l1] = '=';
    memcpy(s + l1 + 1, value, l2 + 1);
    return __putenv(s, l1, s);
}


int putenv(char *s)
{
    size_t l = strchrnul(s, '=') - s;
    if (!l || !s[l])
        return unsetenv(s);
    return __putenv(s, l, 0);
}


char *getenv(const char *name)
{
    size_t l = strchrnul(name, '=') - name;
    if (l && !name[l] && __environ)
        for (char **e = __environ; *e; e++)
            if (!strncmp(name, *e, l) && l[*e] == '=')
                return *e + l + 1;
    return 0;
}

int clearenv()
{
    char **e = __environ;
    __environ = 0;
    if (e)
        while (*e)
            __env_rm_add(*e++, 0);
    return 0;
}

int unsetenv(const char *name)
{
    size_t l = strchrnul(name, '=') - name;
    if (!l || name[l]) {
        errno = EINVAL;
        return -1;
    }
    if (__environ) {
        char **e = __environ, **eo = e;
        for (; *e; e++)
            if (!strncmp(name, *e, l) && l[*e] == '=')
                __env_rm_add(*e, 0);
            else if (eo != e)
                *eo++ = *e;
            else
                eo++;
        if (eo != e)
            *eo = 0;
    }
    return 0;
}

char *secure_getenv(const char *name)
{
    return NULL;
}

