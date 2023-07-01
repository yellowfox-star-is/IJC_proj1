// ppm.h
// Řešení IJC-DU1, příklad b), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0



#ifndef PPM_H
#define PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    unsigned char data[]; // RGB bajty, celkem 3*xsize*ysize };
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif //PPM_H
