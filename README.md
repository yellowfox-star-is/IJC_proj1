# IJC_proj1
This is an implementation of Eratosthenes' sieve in C from my academic time.<br>
The idea is to attempt to implement it in the most efficient way possible, and this is done in two ways:
* Masking:<br>Bits for Eratosthenes' sieve are masked from unsigned longs, ensuring that every single bit is utilized and only a small amount of memory is wasted for padding.
* Macro Implementation of Functions:<br>All functions are implemented as macros, which has two outcomes:
    * The program doesn't waste time calling functions.
    * During compilation, all code is "spilled" into one big file, allowing the compiler to optimize the code more efficiently
