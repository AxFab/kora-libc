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
