// right rotate bits of unsigned int x by n_bits bits

#include "../utils.h"
#include <stdio.h>

void run_r_rotate_bits(unsigned x, int n_bits);
unsigned r_rotate_bits(unsigned x, int n_bits);

int main(void) {
    run_r_rotate_bits(124, 4);
    run_r_rotate_bits(92, 5);
}

void run_r_rotate_bits(unsigned x, int n_bits) {
    printf("result:\t\t%u\n", r_rotate_bits(x, n_bits));
    printf("--------------------------------------------------------------------\n");
}

unsigned r_rotate_bits(unsigned x, int n_bits) {
    if (n_bits < 0) {
        printf("n_bits cannot be less than 0\n");
        return 0;
    }

    printf("x:\t\t");
    print_binary_full(x);
    printf("n_bits:\t\t%d\n\n", n_bits);

    int width = BIT_WIDTH(x);
    printf("int width:\t%d\n", width);

    n_bits %= width;
    if (n_bits > 0) {
        unsigned ones = (unsigned)~0;

        // rightmost n_bits bits of x with 0s to the left
        unsigned r_bits = (~(ones << n_bits)) & x;
        printf("rbits:\t\t");
        print_binary_full(r_bits);

        // shift rightmost bits to leftmost position
        r_bits <<= (width - n_bits);
        printf("rb shifted:\t");
        print_binary_full(r_bits);

        // shift x
        x >>= n_bits;
        printf("x shifted:\t");
        print_binary_full(x);

        x |= r_bits;
        printf("xs | rbs:\t");
        print_binary_full(x);
        printf("\n");
    }
    return x;
}
