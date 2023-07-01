// error.c
// Řešení IJC-DU1, příklad b), 19.3.2020
// Autor: Václav Sysel, FIT
// Přeloženo: gcc 7.5.0

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

void warning_msg(const char *fmt, ...)
{

    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...)
{

    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);

    exit(1);
}
