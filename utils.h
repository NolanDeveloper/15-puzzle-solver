#define arrsize(arr) (sizeof(arr)/sizeof((arr)[0]))

int bitmask_at(uint8_t * mask, unsigned i);
void bitmask_set(uint8_t * mask, unsigned i);
void bitmask_unset(uint8_t * mask, unsigned i);
