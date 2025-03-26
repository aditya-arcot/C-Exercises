// count 1-bits in unsigned int x

#include <stdio.h>

void run_count_bits(unsigned x, int max_print_bits);
int count_bits(unsigned x, int max_print_bits);
void print_binary(unsigned x, int max_print_bits);

int main(void) {
    run_count_bits(104, 8);
    run_count_bits(255, 8);
    run_count_bits((unsigned)~0, 32);
}

void run_count_bits(unsigned x, int max_print_bits) {
    printf("result:\t%d\n", count_bits(x, max_print_bits));
    for (int i = 0; i < 60; i++)
        printf("-");
    printf("\n");
}

int count_bits(unsigned x, int max_print_bits) {
    printf("x:\t");
    print_binary(x, max_print_bits);
    printf("\n");

    // x-1 flips bits starting at rightmost 1-bit and going right
    // x &= (x-1) results in rightmost 1-bit being set to 0
    // process is repeated until x = 0
    // number of iterations is number of 1-bits

    int n = 0;
    while (x > 0) {
        x &= (x - 1);
        printf("%d:\t", ++n);
        print_binary(x, max_print_bits);
    }
    printf("\n");
    return n;
}

void print_binary(unsigned x, int max_print_bits) {
    int bits = sizeof(x) * 8;
    if (bits > max_print_bits) {
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
