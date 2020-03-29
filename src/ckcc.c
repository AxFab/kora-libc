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
    printf("Size int: %d\n", sizeof(int));
    printf("Size long: %d\n", sizeof(long));
    printf("Size size_t: %d\n", sizeof(size_t));
    printf("Size void*: %d\n", sizeof(void *));
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
