#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "priority_queue.h"
#include "utils.h"

void
queue_init(struct PriorityQueue * q) {
    q->size = 0;
    map_init(&q->map);
}

static void
swap_at(struct PriorityQueue * q, unsigned i, unsigned j) {
    unsigned t0;
    uint64_t t1;
    t0 = q->keys[i];
    q->keys[i] = q->keys[j];
    q->keys[j] = t0;
    t1 = q->values[i];
    q->values[i] = q->values[j];
    q->values[j] = t1;
    map_set(&q->map, q->values[i], i);
    map_set(&q->map, q->values[j], j);
}

static void
heap_reduce_key(struct PriorityQueue * q, unsigned position, unsigned k) {
    if (q->keys[position] < k) return; /* don't increase keys */
    q->keys[position] = k;
    if (!position) return;
    unsigned parent = (position + 1) / 2 - 1;
    while (position && q->keys[parent] > q->keys[position]) {
        swap_at(q, position, parent);
        position = parent;
        parent = (position + 1) / 2 - 1;
    }
}

void
queue_add(struct PriorityQueue * q, unsigned k, uint64_t x) {
    if (arrsize(q->keys) <= q->size) {
        printf("Queue overflow.\n");
        exit(-1);
    }
    q->keys[q->size] = UINT_MAX;
    q->values[q->size] = x;
    map_set(&q->map, x, q->size);
    heap_reduce_key(q, q->size, k);
    q->size = q->size + 1;
}

int
queue_is_empty(struct PriorityQueue * q) {
    return !q->size;
}

static void
heapify(struct PriorityQueue * q, unsigned i) {
    unsigned l = (i + 1) * 2 - 1;
    unsigned r = (i + 1) * 2;
    unsigned largest;
    if (l <= q->size && q->keys[l] < q->keys[i]) {
        largest = l;
    } else largest = i;
    if (r <= q->size && q->keys[r] < q->keys[largest]) {
        largest = r;
    }
    if (largest == i) return;
    swap_at(q, i, largest);
    heapify(q, largest);
}

uint64_t
queue_extract_min(struct PriorityQueue * q) {
    if (queue_is_empty(q)) {
        printf("Queue underflow.\n");
        exit(-1);
    }
    uint64_t min = q->values[0];
    map_remove(&q->map, min);
    --q->size;
    q->keys[0] = q->keys[q->size];
    q->values[0] = q->values[q->size];
    map_set(&q->map, q->values[0], 0);
    heapify(q, 0);
    return min;
}

int
queue_has(struct PriorityQueue * q, uint64_t x) {
    return map_has(&q->map, x);
}

void
queue_reduce_key(struct PriorityQueue * q, unsigned k, uint64_t x) {
    unsigned position = map_at(&q->map, x);
    heap_reduce_key(q, position, k);
}

#ifdef TESTING

#include <assert.h>

int main() {
    struct PriorityQueue q;
    queue_init(&q);
    queue_add(&q, 1, 42);
    queue_add(&q, 2, 43);
    queue_add(&q, 0, 44);
    assert(3 == q.size);
    uint64_t min = queue_extract_min(&q);
    assert(44 == min);
    min = queue_extract_min(&q);
    assert(42 == min);
    min = queue_extract_min(&q);
    assert(43 == min);
}

#endif
