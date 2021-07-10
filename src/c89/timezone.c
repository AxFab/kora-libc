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
#include <time.h>
#include <bits/libio.h>
#include <string.h>


long __tz_offset = 0;

// char *timezone(const char *zone, int dst);

void tzset()
{
    // char *ptr;
    // char *tz = getenv("TZ");
    // char *s_tm = strtok_r(tz, " ", &ptr);
    // char *s_off = strtok(NULL, " ", &ptr);
    // char *d_tm = strtok(NULL, " ", &ptr);
    // char *d_off = strtok(NULL, " ", &ptr);
    // char *d_start = strtok(NULL, " ", &ptr);
    // char *d_end = strtok(NULL, " ", &ptr);
}


struct tm *localtime_r(const time_t *restrict timep, struct tm *restrict tp)
{
    tzset();
    time_t ltime = *timep;
    ltime += __tz_offset;
    return gmtime_r(&ltime, tp);
}

struct tm *localtime(const time_t *timep)
{
    static struct tm tm;
    return localtime_r(timep, &tm);
}

size_t strftime_(FILE *fp, const char *str, const struct tm *tm)
{
    int lg;
    char tmp [512];
    char *mxs;

    FLOCK(fp);
    fp->count_ = 0;

    while (*str) {

        /* Write litteral characters */
        if (*str != '%') {
            mxs = strchr(str, '%');
            lg = (mxs == NULL) ? (int)strlen(str) : (int)(mxs - str);
            if (fp->write(fp, str, lg) < 0)
                return -1;

            str += lg;
            continue;
        }

        /* Read format specifier */
        lg = 0;
        switch (str[1]) {
        case 'c': // dim 28 Sep 2003 09:01:25 CET
        case 'D': // 09/28/03
        case 'x': // 09.28.2003
        case 'T': // 21:05:25
        case 'X': // 09:01:25 PM
        case 'a': // Dim
        case 'A': // Dimanche
        case 'b': // Sep
        case 'B': // September
        case 'Z': // CET
        case 'p': // PM
        case 'w': // 0 : 0-6, Dim
        case 'u': // 1:  1-7. Lun
        case 'd': // Jr 02
        case 'e': // Jr 2
        case 'j': // Jr 003
        case 'm': // Mt 09
        case 'S': // 05
        case 'l': // 9 (H12)
        case 'I': // 09 (H12)
        case 'k': // 9 (H24)
        case 'H': // 09 (H24)
        case 'N': // nanoseconds
        case 's': // timestamp (secs)
        case 'n': // \n
            strcpy(tmp, "\n");
            lg = 1;
            break;
        case 't': // \t
            strcpy(tmp, "\t");
            lg = 1;
            break;
        case '%': // %
            strcpy(tmp, "%");
            lg = 1;
            break;
        default:
            break;
        }

        if (fp->write(fp, tmp, lg) < 0)
            return -1;
        str += 2;
    }

    FUNLOCK(fp);
    return fp->count_;
}

size_t strftime(char *buf, size_t len, const char *fmt, const struct tm *tm)
{
    FILE fp;
    __fstr_open_rw(&fp, buf, len);
    return strftime_(&fp, fmt, tm);
}

time_t timelocal(struct tm *tm)
{
    time_t gmt = mktime(tm);
    return gmt - __tz_offset;
}

time_t timegm(struct tm *tm)
{
    return mktime(tm);
}

