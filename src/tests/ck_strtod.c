#include <stdlib.h>
#include <string.h>
#include "check.h"

START_TEST(test_strtod)
{
    char *str;

    double d0  = strtod("467.34", &str);
    ck_ok(d0 == 467.34);
    ck_ok(strcmp(str, "") == 0);

    double d1  = strtod("0.123", &str);
    ck_ok(d1 == 0.123);
    ck_ok(strcmp(str, "") == 0);

    double d2  = strtod("12435.6Time", &str);
    ck_ok(d2 == 12435.6);
    ck_ok(strcmp(str, "Time") == 0);

    double d3  = strtod("0000.0X", &str);
    ck_ok(d3 == 0.0);
    ck_ok(strcmp(str, "X") == 0);

    double d4  = strtod("0000.08a", &str);
    ck_ok(d4 == 0.08);
    ck_ok(strcmp(str, "a") == 0);

    double d5  = strtod("0x34p45!", &str);
    ck_ok(d5 == 0x34p45);
    ck_ok(strcmp(str, "!") == 0);

    double d6  = strtod("12e3 \n", &str);
    ck_ok(d6 == 12e3);
    ck_ok(strcmp(str, " \n") == 0);

}
END_TEST()

void ck_strtod(Suite *s)
{
    ck_test_case(s, test_strtod);
}
