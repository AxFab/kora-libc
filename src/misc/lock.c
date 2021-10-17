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
#include <bits/atomic.h>
#include <bits/futex.h>

void __lock(atomic_int *lock)
{
    if (*lock < 0)
        return;

    int status;
    // Spin loop
    for (int i = 0; i < 100; ++i) {
        status = 0;
        status = atomic_cmpxchg(lock, 0, 1);
        if (status == 0)
            return;
        atomic_break();
    }

    // Lock is now contended
    if (status == 1)
        status = atomic_xchg(lock, 2);

    while (status != 0) {
        // Wait in the kernel
        futex_wait(lock, 2, -1, 0);
        status = atomic_xchg(lock, 2);
    }
}

void __unlock(atomic_int *lock)
{
    if (*lock < 0)
        return;

    // Reset lock to zero
    if (*lock == 2)
        *lock = 0;
    else if (atomic_xchg(lock, 0) == 1)
        return;

    // Spin waiting for a lock
    for (int i = 0; i < 100; ++i) {
        if (*lock) {
            // Lock is still contended
            int status = atomic_cmpxchg(lock, 1, 2);
            if (status != 0)
                return;
        }
        atomic_break();
    }

    // We wake someone up
    futex_wake(lock, 1, 0);
    return;
}
