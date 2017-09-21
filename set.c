#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "utils.h"

void
set_init(struct Set * s) {
    memset(s->filled, 0, sizeof(s->filled));
    s->size = 0;
}

void
set_add(struct Set * s, uint64_t x) {
    if (arrsize(s->values) * 2u / 3u <= s->size) {
        printf("Set overflow.\n");
        exit(-1);
    }
    unsigned i = x % arrsize(s->values);
    while (bitmask_at(s->filled, i)) i = (i + 1) % arrsize(s->values);
    s->values[i] = x;
    bitmask_set(s->filled, i);
    ++s->size;
}

int
set_has(struct Set * s, uint64_t x) {
    unsigned i = x % arrsize(s->values);
    while (bitmask_at(s->filled, i) && s->values[i] != x) {
        i = (i + 1) % arrsize(s->values);
    }
    return bitmask_at(s->filled, i);
}
