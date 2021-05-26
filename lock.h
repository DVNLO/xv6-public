#ifndef LOCK_H
#define LOCK_H

#include "types.h"
#include "x86.h"

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
    while(!xchg(&lk->is_locked, locked))
    {
        continue;
    }
}

void
lock_release(lock_t * const lk)
{
    uint const unlock = 0U;
    lk->is_locked = unlock;
}

#endif