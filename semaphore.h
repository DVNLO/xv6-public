#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct lock_t;

typedef struct
{
    lock_t * lk; // wait lock
    volatile uint count;
} semaphore_t;

void
semaphore_init(semaphore_t * const s, uint const count_val)
{
    s->lk = malloc(sizeof(lock_t));
    lock_init(s->lk);
    s->count = count_val;
}

void
semaphore_wait(semaphore_t * const s)
{
    lock_acquire(s->lk);
    uint initial_count = s->count;
    uint final_count = initial_count - 1;
    while(!initial_count || xchg(&s->count, final_count) != initial_count)
    {
        initial_count = s->count;
        final_count = initial_count - 1;
    }
    lock_release(s->lk);
    __sync_synchronize(); // see spinlock.c
}

void
semaphore_release(semaphore_t * const s)
{
    __sync_synchronize(); // see spinlock.c
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