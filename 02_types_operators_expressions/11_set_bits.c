/*
    set n bits of unsigned int x starting at position p
        to rightmost n bits of unsigned int y

    p is leftmost position of desired portion
    position is right to left with 0 as rightmost bit
*/

#include <stdio.h>

static int max_print_bits = 8;

unsigned set_bits(unsigned x, unsigned y, int p, int n);
void print_binary(unsigned x);

int main(void)
{
    printf("%u\n\n", set_bits(157, 42, 5, 3));
    printf("%u\n\n", set_bits(145, 115, 6, 3));
    printf("%u\n\n", set_bits(255, 0, 6, 2));
}

unsigned set_bits(unsigned x, unsigned y, int p, int n)
{
    if (p < 0)
    {
        printf("p cannot be less than 0\n");
        return 0;
    }
    if (n < 1)
    {
        printf("n cannot be less than 1\n");
        return 0;
    }

    printf("x:\t\t");
    print_binary(x);
    printf("y:\t\t");
    print_binary(y);
    printf("p:\t\t%d\n", p);
    printf("n:\t\t%d\n\n", n);

    unsigned ones = (unsigned)~0;
    // copy segment right bit position
    int shift = p + 1 - n;

    // mask to 0 copy segment
    unsigned x_mask = ~((~(ones << n)) << shift);
    printf("x mask:\t\t");
    print_binary(x_mask);

    x &= x_mask;
    // x now contains 0 in copy segment and original bits everywhere else
    printf("x masked:\t");
    print_binary(x);

    // mask to 0 left of rightmost n bits
    unsigned y_mask = ~(ones << n);
    printf("y mask:\t\t");
    print_binary(y_mask);

    y &= y_mask;
    printf("y masked:\t");
    print_binary(y);

    y <<= shift;
    // y now contains rightmost n bits in copy segment and 0 everywhere else
    printf("y shifted:\t");
    print_binary(y);

    x |= y;
    printf("x | y:\t\t");
    print_binary(x);
    printf("\n");

    return x;
}

void print_binary(unsigned x)
{
    int bits = sizeof(x) * 8;
    if (bits > max_print_bits)
    {
        bits = max_print_bits;
        printf("... ");
    }
    for (int i = bits - 1; i >= 0; i--)
    {
        unsigned bit = (x >> i) & 1;
        printf("%u", bit);
        if (i % 4 == 0)
        {
            printf(" ");
        }
    }
    printf("(%u)\n", x);
}
