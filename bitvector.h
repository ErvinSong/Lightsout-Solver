/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2023                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
/*
 * Bit vectors - fixed-width vectors of bits w/ a toggle function
 *
 * Both implementations and clients should allow for different
 * BITVECTOR_LIMIT values.
 *
 * 15-122 Principles of Imperative Computation */

#include <stdbool.h>
#include <stdint.h>

#ifndef BITVECTOR_H
#define BITVECTOR_H

// typedef _______ bitvector;
typedef uint32_t bitvector;

#define BITVECTOR_LIMIT 25

/* Get a new bitvector with everything set to 'false'. */
bitvector bitvector_new();

/* Get the ith bit of the bitvector n. */
bool bitvector_get(bitvector B, uint8_t i)
  /*@requires 0 <= i < BITVECTOR_LIMIT; @*/ ;

/* Toggle the ith bit of the bitvector n, returning a new bitvector. */
/* The old bitvector remains unchanged. */
bitvector bitvector_flip(bitvector B, uint8_t i)
  /*@requires 0 <= i < BITVECTOR_LIMIT; @*/ ;

/* Compare two bitvectors for equality. */
bool bitvector_equal(bitvector B1, bitvector B2);

#endif
