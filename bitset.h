// bitset.h
// Řešení IJC-DU1, příklad a), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0



#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <limits.h>
#include "error.h"

typedef unsigned long * bitset_t; //type of bit field
typedef unsigned long bitset_index_t; //type of index for bit field

#define number_of_bits (CHAR_BIT * sizeof(bitset_index_t))
#define number_of_bytes (sizeof(bitset_index_t))

#ifdef USE_INLINE

#define bitset_create(jmeno_pole,velikost) _Static_assert(velikost > 0, "Velikost nesmi byt zaporna.");\
bitset_index_t jmeno_pole[((velikost+1)/ number_of_bits) + (((velikost+1)% number_of_bits) == 0? 1 : 2)] = {0,};\
jmeno_pole[0] = velikost;

#define bitset_alloc(jmeno_pole,velikost) \
    _Static_assert(velikost > 0, "Velikost nesmi byt zaporna.");\
    bitset_t jmeno_pole = calloc(velikost / number_of_bits + ((velikost % number_of_bits) ? 1 : 2), sizeof(bitset_index_t));\
    if (jmeno_pole == NULL)\
    {\
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n");\
        exit(EXIT_FAILURE);\
    }\
    jmeno_pole[0] = (unsigned long) velikost

inline void bitset_free(bitset_t jmeno_pole)
{
    free(jmeno_pole);
}


inline bitset_index_t bitset_size(bitset_t jmeno_pole)
{
    return jmeno_pole[0];
}

inline void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,bitset_index_t vyraz)
{
    if(index > jmeno_pole[0])
    {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0]);
    }
    jmeno_pole[(index / number_of_bits) + 1] = ((jmeno_pole[(index / number_of_bits) + 1] & ~(1ul << (index % number_of_bits))) | (((unsigned long) vyraz) << index % number_of_bits));
}

inline bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
    if (index > jmeno_pole[0])
    {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0]);
    }
    return ((jmeno_pole[(index / number_of_bits) + 1] >> (index % number_of_bits)) & ((bitset_index_t) 1));
}

#else



#define bitset_create(jmeno_pole,velikost) _Static_assert(velikost > 0, "Velikost nesmi byt zaporna.");\
bitset_index_t jmeno_pole[((velikost+1)/ number_of_bits) + (((velikost+1)% number_of_bits) == 0? 1 : 2)] = {0,};\
jmeno_pole[0] = velikost;

#define bitset_alloc(jmeno_pole,velikost) \
    _Static_assert(velikost > 0, "Velikost nesmi byt zaporna.");\
    bitset_t jmeno_pole = calloc(velikost / number_of_bits + ((velikost % number_of_bits) ? 1 : 2), sizeof(bitset_index_t));\
    if (jmeno_pole == NULL)\
    {\
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n");\
        exit(EXIT_FAILURE);\
    }\
    jmeno_pole[0] = (unsigned long) velikost

#define bitset_free(jmeno_pole) \
    free(jmeno_pole)

#define bitset_size(jmeno_pole) jmeno_pole[0]

#define bitset_setbit(jmeno_pole,index,vyraz) if(index > jmeno_pole[0]) {error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0]);} jmeno_pole[(index / number_of_bits) + 1] = \
((jmeno_pole[(index / number_of_bits) + 1] & ~(1ul << (index % number_of_bits))) | (((unsigned long) vyraz) << index % number_of_bits))

#define bitset_getbit(jmeno_pole,index) ((index > jmeno_pole[0])?(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)jmeno_pole[0])), 1:1 ,\
((jmeno_pole[(index / number_of_bits) + 1] >> (index % number_of_bits)) & ((bitset_index_t) 1)))

#endif //USE_INLINE

#endif //BITSET_H
