#include <stddef.h>
#include <locale.h>
#include <limits.h>
#include <string.h>
#include <bits/atomic.h>

struct __locale_map {
    const char *name;
};

struct __locale {
    const struct __locale_map *cat[LC_ALL];
};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

static atomic_int __local_lock = 0;

const struct __locale_map *__locale_maps[LC_ALL];

const struct __locale_map __locale_c = {
    "C"
};

static const struct lconv posix_lconv = {
    .decimal_point = ".",
    .thousands_sep = "",
    .grouping = "",
    .int_curr_symbol = "",
    .currency_symbol = "",
    .mon_decimal_point = "",
    .mon_thousands_sep = "",
    .mon_grouping = "",
    .positive_sign = "",
    .negative_sign = "",
    .int_frac_digits = CHAR_MAX,
    .frac_digits = CHAR_MAX,
    .p_cs_precedes = CHAR_MAX,
    .p_sep_by_space = CHAR_MAX,
    .n_cs_precedes = CHAR_MAX,
    .n_sep_by_space = CHAR_MAX,
    .p_sign_posn = CHAR_MAX,
    .n_sign_posn = CHAR_MAX,
    .int_p_cs_precedes = CHAR_MAX,
    .int_p_sep_by_space = CHAR_MAX,
    .int_n_cs_precedes = CHAR_MAX,
    .int_n_sep_by_space = CHAR_MAX,
    .int_p_sign_posn = CHAR_MAX,
    .int_n_sign_posn = CHAR_MAX,
};

const struct __locale_map *__get_locale(int cat, const char *name)
{
    if (strcmp(name, "C") == 0)
        return &__locale_c;
    return NULL;
};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

locale_t __current_locale(void)
{
    return NULL;
}

struct lconv *localeconv(void)
{
    return (void *)&posix_lconv;
}


char *setlocale(int cat, const char *name)
{
    const struct __locale_map *lm;

    if (cat < 0 || cat > LC_ALL)
        return NULL;
    __lock(&__local_lock);

    if (name) {
        lm = __get_locale(cat, name);
        if (lm == NULL) {
            __unlock(&__local_lock);
            return NULL;
        }
        if (cat == LC_ALL) {
            for (int i = 0; i < LC_ALL; ++i)
                __locale_maps[i] = lm;
        } else
            __locale_maps[cat] = lm;

    } else if (cat != LC_ALL)
        lm = __locale_maps[cat];

    if (cat == LC_ALL) {
        // TODO - Build string for all categories.
        __unlock(&__local_lock);
        return "C";
    }
    __unlock(&__local_lock);
    return lm ? (char *)lm->name : "C";
}

