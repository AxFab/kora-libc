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
#ifndef __SEC

#ifndef __ONE
#define __ONE
#else
#define __SEC
#endif

#include "include.c"

#include <bits/cdefs.h>

#include <assert.h>
#include <byteswap.h>
// #include <complex.h>
#include <ctype.h>
// #include <dirent.h>
#include <endian.h>
#include <errno.h>
// #include <fcntl.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h> // From the compilor
#include <libgen.h>
// #include <limits.h>
#include <locale.h>
#include <math.h>
#include <monetary.h>
#include <setjmp.h>
#include <signal.h>
#ifdef __C11
# include <stdalign.h>
#endif
#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#include <wchar.h>

#include <sys/types.h>

#ifndef __MAIN
#define __MAIN
int main()
{
    return 0;
}
#endif

#endif
