#ifndef LOCK_H
#define LOCK_H

#include "types.h"

typedef struct
{
    uint is_locked;
} lock_t;

void lock_init(lock_t * const lk);
void lock_acquire(lock_t * const lk);
void lock_release(lock_t * const lk);

#endif