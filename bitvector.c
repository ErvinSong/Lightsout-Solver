#include <stdbool.h>
#include <stdint.h>
#include "lib/bitvector.h"
#include "lib/contracts.h"

/* Get a new bitvector with everything set to 'false'. */
bitvector bitvector_new()
{
    bitvector new = 0;
    return new;
}

/* Get the ith bit of the bitvector n. */
bool bitvector_get(bitvector B, uint8_t i)
{
    REQUIRES(i < BITVECTOR_LIMIT);
    int temp = (B >> i) & 1;
    if (temp == 1) return true;
    else return false;
}

/* Toggle the ith bit of the bitvector n, returning a new bitvector. */
/* The old bitvector remains unchanged. */
bitvector bitvector_flip(bitvector B, uint8_t i)
{
    REQUIRES(i < BITVECTOR_LIMIT);
    bitvector temp = 1;
    temp = temp << i;
    bitvector new = 0;
    if ((temp & B) > 0){
        new = new | (B - temp);
        return new;
    }
    else{
        new = new | (B + temp);
        return new;
    }
}

/* Compare two bitvectors for equality. */
bool bitvector_equal(bitvector B1, bitvector B2){
    return B1 == B2;
}