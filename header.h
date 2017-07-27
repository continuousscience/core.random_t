#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sil_ext.h>
#include <proto_prim.h>

#define RAND_STATE_SZ (624)

// Mersenne Twister state
typedef struct {
    uint32_t mti; // = RAND_STATE_SZ+1 before initialization
    uint32_t mt[RAND_STATE_SZ]; /* the array for the state vector  */
} Random;

static const unsigned char random_hash[HASH_SIZE+1] = /*!hash!*/;
