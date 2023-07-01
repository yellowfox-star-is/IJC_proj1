// steg-decode.c
// Řešení IJC-DU1, příklad b), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0


#include <stdio.h>
#include "ppm.h"
#include "eratosthenes.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	if (argc < 2)
	{
		error_exit("Not enough arguments.\n");
	}

    struct ppm *obraz;
    obraz = ppm_read(argv[1]);

    if (obraz == NULL)
    {
        goto error;
    }


    unsigned int size = (obraz -> xsize) * (obraz -> ysize) * 3;

    //prepare the sieve
    bitset_alloc(sieve, 8000*8000*3); //implementation maximum
    if (sieve == NULL)
    {
        goto alloc_error;
    }
    Eratosthenes(sieve);


    unsigned char c = 0;
    unsigned int charloc = 0;
    unsigned int charsize = sizeof(char) * CHAR_BIT;
    char *buffer = calloc(size, sizeof(char));
    if (buffer == NULL)
    {
        goto buffer_alloc_error;
    }
    unsigned int bufferloc = 0;
    for (unsigned int i = 22; i < size; i++)
    {
        if (bitset_getbit(sieve, i) == 0)
        {

            c |= ((obraz->data[i]) & 1) << charloc;
            charloc += 1;

            //now we have complete byte, we need to save it
            if (charloc == charsize)
            {
                buffer[bufferloc] = c;
                charloc = 0;
                bufferloc += 1;

                if (c == 0)
                {
                    break;
                }

                c = 0;
            }
        }
    }

    if (buffer[bufferloc - 1] != 0)
    {
        error_exit("Zprava nebyla zakoncena nulou.");
    }

    printf("%s", buffer);


    ppm_free(obraz);
    free(buffer);
    free(sieve);

    return 0;

    buffer_alloc_error: free(sieve);
    alloc_error:
    error: return 1;
}
