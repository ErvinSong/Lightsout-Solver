#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "lib/contracts.h"
#include "lib/bitvector.h"
#include "lib/hdict.h"
#include "lib/xalloc.h"

struct board_data {
  uint8_t test;
  bitvector board;
  struct board_data* back;
  uint8_t row;
  uint8_t col;
};

hdict_key bv_key(hdict_entry entry){
  struct board_data* temp = (struct board_data*)(entry);
  bitvector *result = &(temp -> board);
  return (void*)(result);
}

bool bv_equal(hdict_key B1, hdict_key B2){
  bitvector *result1 = (bitvector*)(B1);
  bitvector *result2 = (bitvector*)(B2);
  return bitvector_equal(*result1, *result2);
}

size_t bv_hash(hdict_key B){
  bitvector* temp = (bitvector*)B;
  size_t result = 0;
  for (uint8_t i = 0; i < BITVECTOR_LIMIT; i++){
    result = (result * 17 + i) * bitvector_get(*temp, i);
  }
  return result;
}

void bv_free(void* entry){
  free(entry);
}

/* Initializes a new hash table with the given capacity */
hdict_t ht_new(size_t capacity)
{
    REQUIRES(capacity > 0);
    hdict_t result = hdict_new(capacity,&bv_key, &bv_equal, &bv_hash, &bv_free);
    ENSURES(result != NULL);
    return result;
}
  /*@requires capacity > 0; @*/
  /*@ensures \result != NULL; @*/

/* ht_lookup(H,B) returns
 * NULL if no struct containing the board B exists in H
 * A struct containing the board B if one exists in H.
 */
struct board_data *ht_lookup(hdict_t H, bitvector B)
{
    REQUIRES(H != NULL);
    return (struct board_data*) hdict_lookup(H, (hdict_key)&B);
}

/* ht_insert(H,e) has no return value, because it should have as
 * a precondition that no struct currently in the hashtable contains
 * the same board as DAT->board.
 */
void ht_insert(hdict_t H, struct board_data *DAT)
{
    REQUIRES(H != NULL);
    REQUIRES(ht_lookup(H, DAT -> board) == NULL);
    hdict_entry e = hdict_insert(H, (hdict_entry)DAT);
    bv_free(e);
}
  /*@requires H != NULL; @*/