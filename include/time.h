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
#ifndef __TIME_H
#define __TIME_H 1

#include <stddef.h>
#include <bits/cdefs.h>
#include <bits/types.h>
#include <bits/timespec.h>

__STDC_GUARD

enum {
    CLOCK_MONOTONIC = 0,
    CLOCK_REALTIME,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID,
};

#define MIN_TO_USEC(s)  ((s)*60000000LL)
#define SEC_TO_USEC(s)  ((s)*1000000LL)
#define MSEC_TO_USEC(s)  ((s)*1000LL)
#define TMSPEC_TO_USEC(t)  ((t).tv_sec*1000000LL+(t).tv_nsec/1000L)

#define CLOCKS_PER_SEC  ((clock_t)1000000)
#define TIME_UTC 1

typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __pid_t pid_t;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;

    long int tm_gmtoff;
    const char *tm_zone;
};

struct sigevent;

struct itimerspec {
    struct timespec it_interval;
    struct timespec it_value;
};




clock_t clock(void);
time_t time(time_t *timer);
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm *tp);

struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
char *asctime(const struct tm *tp);
char *ctime(const time_t *timer);

size_t strftime(char *restrict s, size_t maxsize, const char *restrict format, const struct tm *restrict tp);
int timespec_get(struct timespec *ts, int base);


#ifdef __LOCALE
# include <bits/locale.h>
size_t strftime_l(char *restrict s, size_t maxsize, const char *restrict format, const struct tm *restrict tp, locale_t l);
#endif


struct tm *gmtime_r(const time_t *restrict timer, struct tm *restrict tp);
struct tm *localtime_r(const time_t *restrict timer, struct tm *restrict tp);
char *asctime_r(const struct tm *restrict tp, char *restrict __buf);
char *ctime_r(const time_t *restrict timer, char *restrict buf);

void tzset(void);


int nanosleep(const struct timespec *requested_time, struct timespec *remaining);

int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_settime(clockid_t clock_id, const struct timespec *tp);
int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *req, struct timespec *rem);
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);


int timer_create(clockid_t clock_id, struct sigevent *restrict evp, timer_t *restrict timerid);
int timer_delete(timer_t timerid);
int timer_settime(timer_t timerid, int flags, const struct itimerspec *restrict value, struct itimerspec *restrict ovalue);
int timer_gettime(timer_t timerid, struct itimerspec *__value);
int timer_getoverrun(timer_t timerid);


int stime(const time_t *when);
time_t timegm(struct tm *tp);




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];


#define daylight __daylight
#define timezone __timezone


__STDC_END

#endif  /* __TIME_H */
