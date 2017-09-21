#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "utils.h"

void
map_init(struct Map * m) {
    memset(m->filled, 0, sizeof(m->filled));
    memset(m->deleted, 0, sizeof(m->filled));
    m->size = 0;
}

void
map_remove(struct Map * m, uint64_t key) {
    unsigned i = key % arrsize(m->keys);
    while (bitmask_at(m->deleted, i) ||
            (bitmask_at(m->filled, i) && m->keys[i] != key)) {
        i = (i + 1) % arrsize(m->keys);
    }
    if (!bitmask_at(m->filled, i)) return;
    bitmask_unset(m->filled, i);
    bitmask_set(m->deleted, i);
}

void
map_set(struct Map * m, uint64_t key, uint64_t value) {
    if (arrsize(m->keys) * 2 / 3 <= m->size) {
        printf("Map overflow.\n");
        exit(-1);
    }
    unsigned i = key % arrsize(m->keys);
    while (bitmask_at(m->filled, i) && m->keys[i] != key) {
        i = (i + 1) % arrsize(m->keys);
    }
    if (!bitmask_at(m->filled, i)) {
        bitmask_set(m->filled, i);
        bitmask_unset(m->deleted, i);
        m->keys[i] = key;
        m->values[i] = value;
        ++m->size;
    } else {
        m->values[i] = value;
    }
}

uint64_t
map_at(struct Map * m, uint64_t key) {
    unsigned i = key % arrsize(m->keys);
    while (bitmask_at(m->deleted, i) ||
            (bitmask_at(m->filled, i) && m->keys[i] != key)) {
        i = (i + 1) % arrsize(m->keys);
    }
    if (!bitmask_at(m->filled, i)) {
        printf("No such value in map.\n");
        exit(-1);
    }
    return m->values[i];
}

int
map_has(struct Map * m, uint64_t key) {
    unsigned i = key % arrsize(m->keys);
    while (bitmask_at(m->deleted, i) ||
            (bitmask_at(m->filled, i) && m->keys[i] != key)) {
        i = (i + 1) % arrsize(m->keys);
    }
    return bitmask_at(m->filled, i);
}
