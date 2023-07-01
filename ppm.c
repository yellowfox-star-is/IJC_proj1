// ppm.c
// Řešení IJC-DU1, příklad b), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0

#include "ppm.h"
#include "error.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ppm * ppm_read(const char * filename)
{
    char errmsg[255] = {0, };
    char buffer[255] = {0, };
	signed int check = 0;

    FILE * file = fopen(filename, "rb");

    if (file == NULL)
    {
        strcat(errmsg, "Nepodarilo se otevrit soubor.");
        goto error_end;
    }

    struct ppm * loadedpic; //will send the picture back via this pointer

    //tests if the start of the format is P6
    check = fscanf(file, "%s", buffer);
	if (check != 1) //it is expected, that one item will be loaded
	{
		strcat(errmsg, "Spatny format souboru.");
        goto error_fileformat;
	}
    if (strcmp(buffer, "P6") != 0)
    {
        strcat(errmsg, "Spatny format souboru, nenalezeno P6.");
        goto error_fileformat;
    }

    //loads and tests size of format
    unsigned int xsize = 0;
    unsigned int ysize = 0;
    check = fscanf(file, "%u%u", &xsize, &ysize);
	if (check != 2) //two unsigned are expected
	{
        strcat(errmsg, "Spatny format souboru.");
        goto error_fileformat;
	}
    if (xsize == 0 || ysize == 0)
    {
        strcat(errmsg, "Spatny format souboru, nenalezena velikost.");
        goto error_fileformat;
    }

    //loads and checks if next in format is "255"
    check = fscanf(file, "%s", buffer);
	if (check != 1) //one "255" is expected
	{
        strcat(errmsg, "Spatny format souboru.");
        goto error_fileformat;
	}
    if (strcmp(buffer, "255") != 0)
    {
        strcat(errmsg, "Spatny format souboru, nenalezeno 255.");
        goto error_fileformat;
    }

    //checks if char is big enough in this system
    if (sizeof(char) * CHAR_BIT < 8)
    {
        strcat(errmsg, "Spatny format systemu, char nema alespon 8 bitu, format se na tomto systemu nemuze precist.");
        goto error_fileformat;
    }

    unsigned int size = 3*xsize*ysize;
    //checks if size is too big
    if(size > 8000*8000*3) //implementation limit, can be enlarged if needed
    {
        strcat(errmsg, "Soubor je prilis velky, omezeno implementacnim limitem.");
        goto error_fileformat;
    }

    //everything should be fine, allocate structure and start loading
    loadedpic = malloc(sizeof(struct ppm) + (size + 1) * sizeof(char));
    if (loadedpic == NULL)
    {
        strcat(errmsg, "Nedostatek mista pro nacteni obrazku.");
        goto error_fileformat;
    }

    //skipes whitespaces until \n
    int c = 0;
    while ((c = fgetc(file) != '\n')) {}

    //starts to load data
    loadedpic -> xsize = xsize;
    loadedpic -> ysize = ysize;
    for (unsigned int i = 0; c != EOF || i == size; i++)
    {
        c = fgetc(file);

        //some checking
        if (c == EOF && i < size - 1)
        {
            strcat(errmsg, "Prilis malo binarnich dat.");
            goto error_load;
        }
        if (i > size)
        {
            strcat(errmsg, "Prilis mnoho binarnich dat.");
            goto error_load;
        }

        loadedpic -> data[i] = (char) c;
    }
    loadedpic -> data[size] = 0;

    fclose(file);
    return loadedpic;

    //program jumps here if there are some errors that needs to be done and it would be too crazy to if from it
    error_load: free(loadedpic);
    error_fileformat: fclose(file);
    error_end: error_exit("%s\n", errmsg);
    return NULL;
}

void ppm_free(struct ppm * pointer)
{
    free(pointer);
}
