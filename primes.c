// primes.c
// Řešení IJC-DU1, příklad a), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0



#include <stdio.h>
#include "eratosthenes.h"
#include <time.h>

int main ()
{
    time_t start = clock();

    bitset_create(dobrepole, 500000000ul);

    Eratosthenes(dobrepole);

    bitset_index_t size = bitset_size(dobrepole);

    bitset_index_t a = size;
    for (bitset_index_t i = 0; (i < 10) && (a > 0); a--)
    {
        if (bitset_getbit(dobrepole, a) == 0)
        {
            i++;
        }
    }


    for (; a <= size; a++)
    {
        if (bitset_getbit(dobrepole, a) == 0)
        {
            printf("%lu\n", a);
        }
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    return 0;
}
