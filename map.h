#define MAP_MAX_SIZE (1u << 16)

struct Map {
    uint64_t values[MAP_MAX_SIZE];
    uint64_t keys[MAP_MAX_SIZE];
    uint8_t filled[MAP_MAX_SIZE / 8 + 1];
    uint8_t deleted[MAP_MAX_SIZE / 8 + 1];
    unsigned size;
};

extern void map_init(struct Map * m);
extern void map_remove(struct Map * m, uint64_t key);
extern void map_set(struct Map * m, uint64_t key, uint64_t value);
extern uint64_t map_at(struct Map * m, uint64_t key);
extern int map_has(struct Map * m, uint64_t key);
