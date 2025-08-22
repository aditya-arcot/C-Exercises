/*
    set n_bits bits of unsigned int x starting at position p_left
        to rightmost n_bits bits of unsigned int y

    p_left is leftmost position of desired segment
    position is measured right to left with 0 as rightmost bit
*/

#include "../utils.h"
#include <stdio.h>

void run_set_bits(unsigned x, unsigned y, int p_left, int n_bits);
unsigned set_bits(unsigned x, unsigned y, int p_left, int n_bits);

int main(void) {
    run_set_bits(157, 42, 5, 3);
    run_set_bits(145, 115, 6, 3);
    run_set_bits(255, 0, 6, 2);
}

void run_set_bits(unsigned x, unsigned y, int p_left, int n_bits) {
    printf("result:\t\t%u\n", set_bits(x, y, p_left, n_bits));
    printf("----------------------------------------\n");
}

unsigned set_bits(unsigned x, unsigned y, int p_left, int n_bits) {
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
    printf("y:\t\t");
    print_binary_truncated(y);
    printf("p_left:\t\t%d\n", p_left);
    printf("n_bits:\t\t%d\n\n", n_bits);

    // rightmost bit position of copy segment in x
    int p_right = p_left + 1 - n_bits;

    unsigned ones = (unsigned)~0;
    // contains 0s in copy segment of x
    unsigned x_mask = ~((~(ones << n_bits)) << p_right);
    printf("x mask:\t\t");
    print_binary_truncated(x_mask);

    // clear copy segment bits in x
    x &= x_mask;
    printf("x masked:\t");
    print_binary_truncated(x);

    // contains 0s left of copy segment in y
    unsigned y_mask = ~(ones << n_bits);
    printf("y mask:\t\t");
    print_binary_truncated(y_mask);

    // clear bits left of copy segment in y
    y &= y_mask;
    printf("y masked:\t");
    print_binary_truncated(y);

    // shift to reposition copy segment in y
    y <<= p_right;
    // y now contains rightmost n bits in copy segment and 0 everywhere else
    printf("y shifted:\t");
    print_binary_truncated(y);

    // select bits from x outside of copy segment & bits from y inside copy segment
    x |= y;
    printf("x | y:\t\t");
    print_binary_truncated(x);
    printf("\n");

    return x;
}
