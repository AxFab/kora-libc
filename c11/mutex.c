/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2019  <Fabien Bavent>
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
#include <threads.h>
#include <kora/splock.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <limits.h>


int mtx_init(mtx_t *mtx, int type)
{
    mtx->val = 0;
    mtx->tid = 0;
    mtx->flg = type;
    mtx->cnt = 0;
    return thrd_success;
}

void mtx_destroy(mtx_t *mtx)
{
}

int mtx_timedlock(mtx_t *mtx, const xtime *xt)
{
#if 0
    thrd_t tid = thrd_current();
    if (mtx->tid == tid) {
        if (!(mtx->flg & mtx_recursive))
            __pfails("Deadlock");
        ++mtx->cnt;
        return thrd_success;
    }
#endif

    int old = 0;
    if (atomic_compare_exchange_strong(&mtx->val, &old, 1)) {
        // Le futex était libre car il contenait la valeur 0
        // et maintenant il contient la valeur 1
        mtx->cnt = 0;
#if 0
        mtx->tid = tid;
#endif
        return thrd_success;
    }

    old = atomic_exchange(&mtx->val, 2);
    while (old != 0) {
        // Le mutex contient la valeur 1 : l’autre thread l’a pris
        // ==> Attente tant que le futex a la valeur 1
        futex_wait(&mtx->val, 2); // TODO -- timeout
        old = atomic_exchange(&mtx->val, 2);
    }
    mtx->cnt = 0;
#if 0
    mtx->tid = tid;
#endif
    return thrd_success;
}

int mtx_lock(mtx_t *mtx)
{
    static const xtime xt = { INT_MAX, LONG_MAX };
    return mtx_timedlock(mtx, &xt);
}

int mtx_trylock(mtx_t *mtx)
{
#if 0
    thrd_t tid = thrd_current();
    if (mtx->tid == tid) {
        if (!(mtx->flg & mtx_recursive))
            __pfails("Deadlock");
        ++mtx->cnt;
        return thrd_success;
    }
#endif
    int old = 0;

    if (!atomic_compare_exchange_strong(&mtx->val, &old, 1))
        return thrd_busy;
    // Le futex était libre car il contenait la valeur 0
    // et maintenant il contient la valeur 1
    mtx->cnt = 0;
#if 0
    mtx->tid = tid;
#endif
    return thrd_success;
}

int mtx_unlock(mtx_t *mtx)
{
    if (mtx->cnt > 0) {
        --mtx->cnt;
        return thrd_success;
    }
    mtx->tid = 0;
    int old = atomic_fetch_sub(&mtx->val, 1);
    if (old == 1)
        return thrd_success;
    old = atomic_exchange(&mtx->val, 0);
    futex_wakeup(&mtx->val, 1);
    return thrd_success;
}

