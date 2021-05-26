#ifndef LOCK_H
#define LOCK_H

typedef struct
{
    volatile uint is_locked;
} lock_t;

void
lock_init(lock_t * const lk)
{
    lk->is_locked = 0U;
}

void
lock_acquire(lock_t * const lk)
{
    uint const locked = 1U;
    uint i = 0;
    uint j = 32;
    while(xchg(&lk->is_locked, locked) != 0)
    {
        for(i = 0; i < j; ++i)
        {
            continue;
        }
        j *= 2; // exponential backoff
        continue;
    }
    __sync_synchronize();   // see spinlock.c
    i += 1; // confuse compiler
    j += 1;
}

void
lock_release(lock_t * const lk)
{
    uint const unlock = 0U;
    xchg(&lk->is_locked, unlock);
}

#endif