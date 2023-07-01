// eratosthenes.c
// Řešení IJC-DU1, příklad a), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0

#include <stdio.h>
#include <math.h>
#include "bitset.h"
#include "eratosthenes.h"

void Eratosthenes(bitset_t pole)
{
    bitset_index_t size = bitset_size(pole);
    bitset_index_t max = sqrt(bitset_size(pole));

    for (bitset_index_t i = 0; i <= 1; i++) //nastaví 0 a 1 že nejsou prvočísla
    {
        bitset_setbit(pole, i, 1);
    }

    for (bitset_index_t x = 0; x <= max; x++)
    {
        if (!bitset_getbit(pole, x))
        {
            for (bitset_index_t y = x + x; y <= size; y += x)
            {
                bitset_setbit(pole, y, 1);
            }
        }
    }

}
