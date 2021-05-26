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
    while(xchg(&lk->is_locked, locked) != 0)
    {
        continue;
    }
    __sync_synchronize();
}

void
lock_release(lock_t * const lk)
{
    uint const unlock = 0U;
    __sync_synchronize();
    xchg(&lk->is_locked, unlock);
}

#endif