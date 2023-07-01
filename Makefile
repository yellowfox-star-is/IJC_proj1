# Makefile
# Řešení IJC-DU1, příklad ab), 19.3.2020
# Autor: Václav Sysel, FIT
# Přeloženo: gcc 7.5.0
#

CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2

all: primes primes-i steg-decode

primes: primes.o eratosthenes.o error.o bitset.h
	gcc $(CFLAGS) primes.o eratosthenes.o error.o -o primes -lm
	
primes-i: primes-i.o eratosthenes-i.o bitset-i.o error.o
	gcc $(CFLAGS) primes-i.o eratosthenes-i.o bitset-i.o error.o -o primes-i -lm

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	gcc $(CFLAGS) steg-decode.o ppm.o error.o eratosthenes.o -o steg-decode -lm

#files for primes
#=======================
primes.o: primes.c eratosthenes.h
	gcc $(CFLAGS) -c primes.c -lm

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	gcc $(CFLAGS) -c eratosthenes.c

error.o: error.c error.h
	gcc $(CFLAGS) -c error.c

#files for primes-i
#=======================
primes-i.o: primes.c eratosthenes.h
	gcc $(CFLAGS) -c -DUSE_INLINE primes.c -lm -o primes-i.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	gcc $(CFLAGS) -c -DUSE_INLINE eratosthenes.c -o eratosthenes-i.o

bitset-i.o: bitset.c bitset.h
	gcc $(CFLAGS) -c -DUSE_INLINE bitset.c -o bitset-i.o

#files for steg-decode
#=======================
steg-decode.o: steg-decode.c ppm.h eratosthenes.h
	gcc $(CFLAGS) -c steg-decode.c

ppm.o: ppm.c ppm.h error.h
	gcc $(CFLAGS) -c ppm.c

#way of use
#=======================

clean:
	rm *.o primes primes-i steg-decode

run: all
	ulimit -s 65000 && ./primes
	ulimit -s 65000 && ./primes-i
