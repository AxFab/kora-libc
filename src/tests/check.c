#include "check.h"

Suite *__ck_suite = NULL;

void ck_strtod(Suite *s);

int main(int argc, char const *argv[])
{
    Suite s;
    memset(&s, 0, sizeof(s));
    ck_strtod(&s);
    ck_run(&s);
    return 0;
}
