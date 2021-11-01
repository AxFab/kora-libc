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
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    int i = sizeof(int);
    int l = sizeof(long);
    int j = sizeof(size_t);
    int p = sizeof(void *);
    printf("Page size: %d\n", (int)sysconf(_SC_PAGESIZE));
    printf("Size int: %d\n", (int)sizeof(int));
    printf("Size long: %d\n", (int)sizeof(long));
    printf("Size size_t: %d\n", (int)sizeof(size_t));
    printf("Size void*: %d\n", (int)sizeof(void *));
    if (sizeof(char) != 1)
        printf("Warning: char size is not size of byte!\n");
    if (j != p)
        printf("Warning: bad assertion size_t and void* have same size.\n");
    if (sizeof(short) != 2)
        printf("Warning: unable to support 16bits words\n");
    if (i == p) {
        if (l == p)
            printf("  __ILP%d\n", p * 8);
        else
            printf("  __IP%d\n", p * 8);
    } else {
        if (l == p)
            printf("  __LP%d\n", p * 8);
        else if (sizeof(long long) == p)
            printf("  __LLP%d\n", p * 8);
        else
            printf("  WIERDO!");
    }
    printf("hostname max: %d\n", (int)sysconf(_SC_HOST_NAME_MAX));
    printf("open files max: %d\n", (int)sysconf(_SC_OPEN_MAX));
    printf("login max: %d\n", (int)sysconf(_SC_LOGIN_NAME_MAX));
    printf("freq: %d\n", (int)sysconf(_SC_CLK_TCK));
    return 0;
}
