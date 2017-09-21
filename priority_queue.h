#define PRIORITY_QUEUE_MAX_SIZE (1u << 16)

struct PriorityQueue {
    unsigned keys[PRIORITY_QUEUE_MAX_SIZE];
    uint64_t values[PRIORITY_QUEUE_MAX_SIZE];
    unsigned size;
    void * p;
    struct Map map;
};

extern void queue_init(struct PriorityQueue * q);
extern void queue_add(struct PriorityQueue * q, unsigned k, uint64_t x);
extern int queue_is_empty(struct PriorityQueue * q);
extern uint64_t queue_extract_min(struct PriorityQueue * q);
extern int queue_has(struct PriorityQueue * q, uint64_t x);
extern void queue_reduce_key(struct PriorityQueue * q, unsigned k, uint64_t x);
