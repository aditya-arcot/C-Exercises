// count 1-bits in unsigned int x

#include "../utils.h"
#include <stdio.h>

void run_count_bits(unsigned x);
int count_bits(unsigned x);

int main(void) {
    run_count_bits(104);
    run_count_bits(255);
    run_count_bits((unsigned)~0);
}

void run_count_bits(unsigned x) {
    printf("result:\t%d\n", count_bits(x));
    for (int i = 0; i < 60; i++)
        printf("-");
    printf("\n");
}

int count_bits(unsigned x) {
    printf("x:\t");
    print_binary_full(x);
    printf("\n");

    // x-1 flips bits starting at rightmost 1-bit and going right
    // x &= (x-1) results in rightmost 1-bit being set to 0
    // process repeats until x = 0
    // number of iterations is number of 1-bits

    int n = 0;
    while (x > 0) {
        x &= (x - 1);
        printf("%d:\t", ++n);
        print_binary_full(x);
    }
    printf("\n");
    return n;
}
