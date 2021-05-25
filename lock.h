#ifndef LOCK_H
#define LOCK_H

#include "types.h"

typedef struct
{
    uint is_locked;
} lock_t;

int lock_init(lock_t * const lk);
int lock_acquire(lock_t * const lk);
int lock_release(lock_t * const lk);

#endif