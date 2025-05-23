// right rotate bits of unsigned int x by n positions

#include <stdio.h>

void run_r_rotate_bits(unsigned x, int n);
unsigned r_rotate_bits(unsigned x, int n);
int int_length(void);
void print_binary(unsigned x);

int main(void) {
    run_r_rotate_bits(124, 4);
    run_r_rotate_bits(92, 5);
}

void run_r_rotate_bits(unsigned x, int n) {
    printf("result:\t\t%u\n", r_rotate_bits(x, n));
    printf("------------------------------------------------------------\n");
}

unsigned r_rotate_bits(unsigned x, int n) {
    if (n < 0) {
        printf("n cannot be less than 0\n");
        return 0;
    }

    printf("x:\t\t");
    print_binary(x);
    printf("n:\t\t%d\n\n", n);

    int length = int_length();
    printf("int length:\t%d\n", length);

    n %= length;
    if (n > 0) {
        unsigned ones = (unsigned)~0;

        // rightmost n bits of x with 0s to the left
        unsigned r_bits = (~(ones << n)) & x;
        printf("rbits:\t\t");
        print_binary(r_bits);

        // shift rightmost bits to leftmost position
        r_bits <<= (length - n);
        printf("rb shifted:\t");
        print_binary(r_bits);

        // shift x
        x >>= n;
        printf("x shifted:\t");
        print_binary(x);

        x |= r_bits;
        printf("xs | rbs:\t");
        print_binary(x);
        printf("\n");
    }
    return x;
}

int int_length(void) {
    int i;
    unsigned ones = (unsigned)~0;
    for (i = 1; (ones >>= 1) > 0; i++)
        ;
    return i;
}

void print_binary(unsigned x) {
    int bits = sizeof(x) * 8;
    for (int i = bits - 1; i >= 0; i--) {
        unsigned bit = (x >> i) & 1;
        printf("%u", bit);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("(%u)\n", x);
}
