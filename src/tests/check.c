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
#include "check.h"
#include <time.h>
#include <bits/xtime.h>

Suite *__ck_suite = NULL;

void ck_strtod(Suite *s);
void ck_heap(Suite *s);

void futex_wait() {}
void futex_wake() {}
void futex_requeue() {}
xtime_t xtime_read(int clockid) { time(NULL) * 1000000ULL; }
// void pspawn() {}

int main(int argc, char const *argv[])
{
    Suite s;
    memset(&s, 0, sizeof(s));
    ck_strtod(&s);
    ck_heap(&s);
    return ck_run(&s) ? -1 : 0;
}
