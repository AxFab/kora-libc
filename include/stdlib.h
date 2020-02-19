#ifndef __STDLIB_H
#define __STDLIB_H 1


#include <bits/cdefs.h>
#include <stddef.h>



// # 1 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 1 3 4
// # 50 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4
typedef enum {
    P_ALL,
    P_PID,
    P_PGID
} idtype_t;

// # 1 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 1 3 4


#include <sys/types.h>



typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long int quot;
    long int rem;
} ldiv_t;

typedef struct {
    long long int quot;
    long long int rem;
} lldiv_t;



size_t ctype_get_mb_cur_max(void);




double atof(const char *nptr);
int atoi(const char *nptr);
long int atol(const char *nptr);

long long int atoll(const char *nptr);





double strtod(const char *restrict nptr, char **restrict endptr);
float strtof(const char *restrict nptr, char **restrict endptr);
long double strtold(const char *restrict nptr, char **restrict endptr);

long int strtol(const char *restrict nptr, char **restrict endptr, int base);
unsigned long int strtoul(const char *restrict nptr, char **restrict endptr, int base);
long long int strtoq(const char *restrict nptr, char **restrict endptr, int base);
unsigned long long int strtouq(const char *restrict nptr,  char **restrict endptr, int base);
long long int strtoll(const char *restrict nptr, char **restrict endptr, int base);
unsigned long long int strtoull(const char *restrict nptr, char **restrict endptr, int base);

char *l64a(long int n);
long int a64l(const char *s);











long int random(void);
void srandom(unsigned int seed);

char *initstate(unsigned int seed, char *statebuf, size_t statelen);
char *setstate(char *statebuf);


struct random_data {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
};

int random_r(struct random_data *restrict buf, int32_t *restrict result);
int srandom_r(unsigned int seed, struct random_data *buf);
int initstate_r(unsigned int seed, char *restrict statebuf, size_t statelen,  struct random_data *restrict buf);
int setstate_r(char *restrict statebuf, struct random_data *restrict buf);



int rand(void);
void srand(unsigned int seed);
int rand_r(unsigned int *seed);


double drand48(void);
double erand48(unsigned short int xsubi[3]);


long int lrand48(void);
long int nrand48(unsigned short int xsubi[3]);


long int mrand48(void);
long int jrand48(unsigned short int xsubi[3]);


void srand48(long int seedval);
unsigned short int *seed48(unsigned short int seed16v[3]);
void lcong48(unsigned short int param[7]);



struct drand48_data {
    unsigned short int x[3];
    unsigned short int old_x[3];
    unsigned short int c;
    unsigned short int init;
    unsigned long long int a;

};


int drand48_r(struct drand48_data *restrict buffer, double *restrict result);
int erand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer, double *restrict result);


int lrand48_r(struct drand48_data *restrict buffer, long int *restrict result);
int nrand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer,  long int *restrict result);


int mrand48_r(struct drand48_data *restrict buffer, long int *restrict result);
int jrand48_r(unsigned short int xsubi[3], struct drand48_data *restrict buffer, long int *restrict result);


int srand48_r(long int seedval, struct drand48_data *buffer);

int seed48_r(unsigned short int seed16v[3],  struct drand48_data *buffer);

int lcong48_r(unsigned short int param[7],  struct drand48_data *buffer);




#include <bits/alloc.h>

// # 1 "/usr/include/alloca.h" 1 3 4
// # 24 "/usr/include/alloca.h" 3 4
// # 1 "/usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h" 1 3 4
// # 25 "/usr/include/alloca.h" 2 3 4
void *alloca(size_t size);







_Noreturn void abort(void);
int atexit(void (*func)(void));
int at_quick_exit(void (*func)(void));
int on_exit(void (*func)(int status, void *arg), void *arg);
_Noreturn void exit(int status);
_Noreturn void quick_exit(int status);
_Noreturn void _Exit(int status);

char *getenv(const char *name);
int putenv(char *string);
int setenv(const char *name, const char *value, int replace);
int unsetenv(const char *name);
int clearenv(void);


char *mktemp(char *template);
int mkstemp(char *template);
int mkstemps(char *template, int suffixlen);
char *mkdtemp(char *template);


int system(const char *command) ;
char *realpath(const char *restrict name, char *restrict resolved);




typedef int (*compar_fn_t)(const void *, const void *);



void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, compar_fn_t compar);
void qsort(void *base, size_t nmemb, size_t size, compar_fn_t compar);

int abs(int x);
long int labs(long int x);
long long int llabs(long long int x);







div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);



char *ecvt(double value, int ndigit, int *restrict decpt, int *restrict sign);
char *fcvt(double value, int ndigit, int *restrict decpt, int *restrict sign);
char *gcvt(double value, int ndigit, char *buf);
char *qecvt(long double value, int ndigit, int *restrict decpt, int *restrict sign);
char *qfcvt(long double value, int ndigit, int *restrict decpt, int *restrict sign);
char *qgcvt(long double value, int ndigit, char *buf);

int ecvt_r(double value, int ndigit, int *restrict decpt,  int *restrict sign, char *restrict buf, size_t len);
int fcvt_r(double value, int ndigit, int *restrict decpt,  int *restrict sign, char *restrict buf, size_t len);
int qecvt_r(long double value, int ndigit, int *restrict decpt, int *restrict sign, char *restrict buf, size_t len);
int qfcvt_r(long double value, int ndigit, int *restrict decpt, int *restrict sign, char *restrict buf, size_t len);


int mblen(const char *s, size_t n);
int mbtowc(wchar_t *restrict pwc, const char *restrict s, size_t n);
int wctomb(char *s, wchar_t wchar);
size_t mbstowcs(wchar_t *restrict pwcs, const char *restrict s, size_t n);
size_t wcstombs(char *restrict s, const wchar_t *restrict pwcs, size_t n);




int rpmatch(const char *response);
int getsubopt(char **restrict optionp, char *const *restrict tokens, char **restrict valuep);
int getloadavg(double loadavg[], int nelem);

// # 1 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 1 3 4


#define EXIT_SUCCESS  0
#define EXIT_FAILURE  (!0)



#endif  /* __STDLIB_H */
