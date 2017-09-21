#define SET_MAX_SIZE (1u << 16)

struct Set {
    uint64_t values[SET_MAX_SIZE];
    uint8_t filled[SET_MAX_SIZE / 8 + 1];
    unsigned size;
};

extern void set_init(struct Set * s);
extern void set_add(struct Set * s, uint64_t x);
extern int set_has(struct Set * s, uint64_t x);
