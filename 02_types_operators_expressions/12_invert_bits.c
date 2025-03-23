/*
    invert n bits of unsigned int x starting at position p

    p is leftmost position of desired portion
    position is right to left with 0 as rightmost bit
*/

#include <stdio.h>

static int max_print_bits = 8;

unsigned invert_bits(unsigned x, int p, int n);
void print_binary(unsigned x);

int main(void) {
    printf("%u\n\n", invert_bits(66, 4, 2));
    printf("%u\n\n", invert_bits(0, 3, 1));
    printf("%u\n\n", invert_bits(255, 7, 3));
}

unsigned invert_bits(unsigned x, int p, int n) {
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

    unsigned ones = (unsigned)~0;
    // copy segment right bit position
    int shift = p + 1 - n;

    // mask with 1s in invert segment and 0s everywhere else
    unsigned mask = (~(ones << n)) << shift;
    printf("mask:\t\t");
    print_binary(mask);

    // xor inverts A when B is 1 (in invert segment)
    x ^= mask;
    printf("x ^ mask:\t");
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
