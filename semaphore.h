#ifndef SEMAPHORE_H
#define SEMAPHORE_H

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
        final_count = initial_count - 1;
        if(!initial_count)
        {
            continue; // resource unavailable
        }
    }
    while(xchg(&s->count, final_count) != initial_count);
    __sync_synchronize();   // see spinlock.c
}

void
semaphore_release(semaphore_t * const s)
{
    __sync_synchronize();   // see spinlock.c
    uint initial_count;
    uint final_count;
    do
    {
        initial_count = s->count;
        final_count = initial_count + 1;
    }
    while(xchg(&s->count, final_count) != initial_count);
}

#endif