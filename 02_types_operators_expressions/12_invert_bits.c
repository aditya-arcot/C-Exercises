/*
    invert n_bits bits of unsigned int x starting at position p_left

    p_left is leftmost position of desired segment
    position is measured right to left with 0 as rightmost bit
*/

#include "print_binary.h"
#include <stdio.h>

void run_invert_bits(unsigned x, int p_left, int n_bits);
unsigned invert_bits(unsigned x, int p_left, int n_bits);

int main(void) {
    run_invert_bits(66, 4, 2);
    run_invert_bits(0, 3, 1);
    run_invert_bits(255, 7, 3);
}

void run_invert_bits(unsigned x, int p_left, int n_bits) {
    printf("result:\t\t%u\n", invert_bits(x, p_left, n_bits));
    printf("----------------------------------------\n");
}

unsigned invert_bits(unsigned x, int p_left, int n_bits) {
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

    unsigned ones = (unsigned)~0;
    // contains 1s in segment & 0s outside
    unsigned mask = (~(ones << n_bits)) << p_right;
    printf("mask:\t\t");
    print_binary_truncated(mask);

    // xor inverts x where mask is 1 (in segment)
    x ^= mask;
    printf("x ^ mask:\t");
    print_binary_truncated(x);
    printf("\n");

    return x;
}
