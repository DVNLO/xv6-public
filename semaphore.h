#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "types.h"
#include "x86.h"

typedef struct
{
    volatile uint count;
} semaphore_t;

void
semaphore_init(semaphore_t * const s, uint const count_val)
{
    s->count = count_val;
}

void
semaphore_wait(semaphore_t * const s)
{
    uint initial_count;
    uint final_count;
    do
    {
        initial_count = s->count;
        if(!initial_count)
        {
            continue; // resource unavailable
        }
        final_count = initial_count - 1;
    }
    while(xchg(&s->count, final_count) != initial_count);
}

void
semaphore_release(semaphore_t * const s)
{
    s->count += 1;
}

#endif