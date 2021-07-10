#include "check.h"

Suite *__ck_suite = NULL;

void ck_strtod(Suite *s);

void futex_wait() {}
void futex_wake() {}
void futex_requeue() {}
void pspawn() {}
void xtime_read() {}

int main(int argc, char const *argv[])
{
    Suite s;
    memset(&s, 0, sizeof(s));
    ck_strtod(&s);
    return ck_run(&s) ? -1 : 0;
}
