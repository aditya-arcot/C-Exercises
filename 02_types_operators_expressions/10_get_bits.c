/*
    get n_bits bits from unsigned int x starting at position p_left

    p_left is leftmost position of desired segment
    position is measured right to left with 0 as rightmost bit
*/

#include "../utils.h"
#include <stdio.h>

void run_get_bits(unsigned x, int p_left, int n_bits);
unsigned get_bits(unsigned x, int p_left, int n_bits);

int main(void) {
    run_get_bits(214, 4, 2);
    run_get_bits(214, 7, 4);
    run_get_bits(255, 5, 1);
}

void run_get_bits(unsigned x, int p_left, int n_bits) {
    printf("result:\t\t%u\n", get_bits(x, p_left, n_bits));
    printf("----------------------------------------\n");
}

unsigned get_bits(unsigned x, int p_left, int n_bits) {
    if (p_left < 0) {
        printf("p_left cannot be less than 0\n");
        return 0;
    }
    if (n_bits < 1) {
        printf("n_bits cannot be less than 1\n");
        return 0;
    }

    printf("x:\t\t");
    print_binary_truncated(x);
    printf("p_left:\t\t%d\n", p_left);
    printf("n_bits:\t\t%d\n\n", n_bits);

    // rightmost bit position of segment
    int p_right = p_left + 1 - n_bits;
    // shift to reposition segment
    x >>= p_right;
    printf("shifted:\t");
    print_binary_truncated(x);

    unsigned ones = (unsigned)~0;
    // contains 0s left of shifted segment
    unsigned mask = ~(ones << n_bits);
    printf("mask:\t\t");
    print_binary_truncated(mask);

    // clear bits left of shifted segment
    x &= mask;
    printf("x & mask:\t");
    print_binary_truncated(x);
    printf("\n");

    return x;
}
