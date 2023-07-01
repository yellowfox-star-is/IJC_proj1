// bitset.c
// Řešení IJC-DU1, příklad a), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0



#ifdef USE_INLINE


#include "bitset.h"

extern void bitset_free(bitset_t jmeno_pole);

extern bitset_index_t bitset_size(bitset_t jmeno_pole);

extern void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,bitset_index_t vyraz);

extern bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif //USE_INLINE
