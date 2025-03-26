/*
    get n bits from unsigned int x starting at position p

    p is leftmost position of desired portion
    position is right to left with 0 as rightmost bit
*/

#include <stdio.h>

static int max_print_bits = 12;

void run_get_bits(unsigned x, int p, int n);
unsigned get_bits(unsigned x, int p, int n);
void print_binary(unsigned x);

int main(void) {
    run_get_bits(214, 4, 2);
    run_get_bits(214, 7, 4);
    run_get_bits(255, 5, 1);
}

void run_get_bits(unsigned x, int p, int n) {
    printf("result:\t\t%u\n", get_bits(x, p, n));
    printf("----------------------------------------\n");
}

unsigned get_bits(unsigned x, int p, int n) {
    if (p < 0) {
        printf("p cannot be less than 0\n");
        return 0;
    }
    if (n < 1) {
        printf("n cannot be less than 1\n");
        return 0;
    }

    printf("x:\t\t");
    print_binary(x);
    printf("p:\t\t%d\n", p);
    printf("n:\t\t%d\n\n", n);

    // copy segment right bit position
    int shift = p + 1 - n;

    unsigned ones = (unsigned)~0;
    // shift to get rid of bits right of segment
    x >>= shift;
    printf("shifted:\t");
    print_binary(x);

    // mask to 0 left of segment
    unsigned mask = ~(ones << n);
    printf("mask:\t\t");
    print_binary(mask);

    x &= mask;
    printf("x & mask:\t");
    print_binary(x);
    printf("\n");

    return x;
}

void print_binary(unsigned x) {
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
