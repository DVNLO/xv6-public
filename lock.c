#include "lock.h"
#include "x86.h"

void
lock_init(lock_t * const lk)
{
    lk->is_locked = 0U;
}

void
lock_acquire(lock_t * const lk)
{
    while(xchg(&lk->is_locked, 1) != 0)
    {
        continue;
    }
    printf(1, "acquired\n");
}

void
lock_release(lock_t * const lk)
{
    xchg(&lk->is_locked, 0);
    printf(1, "released\n");
}