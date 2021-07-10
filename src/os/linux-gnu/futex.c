#include <bits/futex.h>
#include <sys/syscall.h>
#include "syscallno.h"

#define FUTEX_WAIT      0
#define FUTEX_WAKE      1
#define FUTEX_FD        2
#define FUTEX_REQUEUE       3
#define FUTEX_CMP_REQUEUE   4
#define FUTEX_WAKE_OP       5
#define FUTEX_LOCK_PI       6
#define FUTEX_UNLOCK_PI     7
#define FUTEX_TRYLOCK_PI    8
#define FUTEX_WAIT_BITSET   9
#define FUTEX_WAKE_BITSET   10
#define FUTEX_WAIT_REQUEUE_PI   11
#define FUTEX_CMP_REQUEUE_PI    12

#define FUTEX_PRIVATE_FLAG  128
#define FUTEX_CLOCK_REALTIME    256

#define FUTEX_PRIORITY  1
#define FUTEX_REALTIME  2
#define FUTEX_SHARED  4
#define FUTEX_CREATE  8


// long futex(uint32_t *uaddr, int futex_op, uint32_t val,
//     const struct timespec *timeout,   /* or: uint32_t val2 */
//                  uint32_t *uaddr2, uint32_t val3);

int futex_wait(volatile int *addr, int val, long timeout, int flags)
{
    return syscall(SYS_futex, addr, FUTEX_WAIT | flags, val, timeout, NULL, 0);
}

int futex_wake(volatile int *addr, int val, int flags)
{
    return syscall(SYS_futex, addr, FUTEX_WAKE | flags, 0, NULL, NULL, 0);
}

int futex_requeue(volatile int *addr, int val, int val2, int *addr2, int flags)
{
    return syscall(SYS_futex, addr, FUTEX_REQUEUE | flags, val, val2, addr2, 0);
}
