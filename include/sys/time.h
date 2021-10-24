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
#ifndef _SYS_TIME_H
#define _SYS_TIME_H 1

#include <bits/types.h>

struct timeval {
   long    tv_sec;         /* seconds */
   long    tv_usec;        /* and microseconds */
};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *tv, void *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

int adjtime(const struct timeval *tv, struct timeval *olddelta);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

typedef enum {
    ITIMER_READ = 0,
    ITIMER_VIRTUAL = 1,
    ITIMER_PROF = 2,
} __itimer_which;

struct itimerval {
    struct timeval it_interval;
    struct timeval it_value;
};


int getitimer(__itimer_which which, struct itimerval *value);
int setitimer(__itimer_which which, const struct itimerval *value, const struct itimerval *oldvalue);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

struct utimbuf {
    __time_t actime;       /* access time */
    __time_t modtime;      /* modification time */
};


int utime(const char *filename, const struct utimbuf *times);
int utimes(const char *filename, const struct timeval times[2]);

int lutimes(const char *filename, const struct timeval times[2]);
int futimes(int fd, const struct timeval times[2]);

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#define timerisset(tvp)     ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp)     ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timercmp(a,b,CMP)   (((a)->tv_sec == (b)->tv_sec) \
    ? ((a)->tv_usec CMP (b)->tv_usec) \
    : ((a)->tv_sec CMP (b)->tv_sec))
#define timeradd(a,b,r)     do { \
    (r)->tv_sec = (a)->tv_sec + (b)->tv_sec; \
    (r)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
        if ((r)->tv_usec > 1000000) { \
            (r)->tv_sec++; \
            (r)->tv_sec -= 1000000; \
        } \
    } while(0)
#define timersub(a,b,r)     do { \
    (r)->tv_sec = (a)->tv_sec - (b)->tv_sec; \
    (r)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
        if ((r)->tv_usec < 0) { \
            (r)->tv_sec--; \
            (r)->tv_sec += 1000000; \
        } \
    } while(0)

#endif /* _SYS_TIME_H */
