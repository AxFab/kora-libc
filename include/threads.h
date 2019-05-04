#ifndef __THREADS_H
#define __THREADS_H 1

#include <time.h>
#include <stdatomic.h>

#define ONCE_FLAG_INIT {0}
#define TSS_DTOR_ITERATIONS 1

typedef int thrd_t;
typedef long tss_t;

typedef struct cnd {

} cnd_t;

typedef struct mtx {
    atomic_int val;
    thrd_t tid;
    int flg;
    int cnt;
} mtx_t;

typedef struct once_flag_t {
    atomic_int status;
} once_flag;


typedef void (*tss_dtor_t)(void *);
typedef int (*thrd_start_t)(void *);

struct xtime {
    time_t sec;
    long nsec;
};
typedef struct xtime xtime;

enum {
    mtx_plain     = 0,
    mtx_try       = 1,
    mtx_timed     = 2,
    mtx_recursive = 4
};

enum {
    thrd_success = 0, // succeeded
    thrd_timeout,     // timeout
    thrd_error,       // failed
    thrd_busy,        // resource busy
    thrd_nomem        // out of memory
};

void call_once(once_flag *flag, void (*func)(void));

int cnd_broadcast(cnd_t *cond);
void cnd_destroy(cnd_t *cond);
int cnd_init(cnd_t *cond);
int cnd_signal(cnd_t *cond);
int cnd_timedwait(cnd_t *cond, mtx_t *mtx, const xtime *xt);
int cnd_wait(cnd_t *cond, mtx_t *mtx);

void mtx_destroy(mtx_t *mtx);
int mtx_init(mtx_t *mtx, int type);
int mtx_lock(mtx_t *mtx);
int mtx_timedlock(mtx_t *mtx, const xtime *xt);
int mtx_trylock(mtx_t *mtx);
int mtx_unlock(mtx_t *mtx);

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
thrd_t thrd_current(void);
int thrd_detach(thrd_t thr);
int thrd_equal(thrd_t thr0, thrd_t thr1);
void thrd_exit(int res);
int thrd_join(thrd_t thr, int *res);
void thrd_sleep(const xtime *xt);
void thrd_yield(void);

int tss_create(tss_t *key, tss_dtor_t dtor);
void tss_delete(tss_t key);
void *tss_get(tss_t key);
int tss_set(tss_t key, void *val);

int xtime_get(xtime *xt, int base);
#define TIME_UTC  1


#endif  /* __THREADS_H */
