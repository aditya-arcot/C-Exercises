#include "print_binary.h"
#include <stdbool.h>
#include <stdio.h>

static const int max_print_bits = 12;

/*
prints binary representation of x

params:
    x - unsigned int to print
    truncate - if true, truncates to max_print_bits with leading "..."
*/
static void print_binary(unsigned x, bool truncate) {
    int bits = BIT_WIDTH(x);
    if (truncate && bits > max_print_bits) {
        bits = max_print_bits;
        printf("... ");
    }
    for (int i = bits - 1; i >= 0; i--) {
        unsigned bit = (x >> i) & 1;
        printf("%u", bit);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("(%u)\n", x);
}

void print_binary_truncated(unsigned x) {
    print_binary(x, true);
}

void print_binary_full(unsigned x) {
    print_binary(x, false);
}
