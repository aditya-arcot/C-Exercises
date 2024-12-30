// count 1-bits in unsigned int x

#include <stdio.h>

int count_bits(unsigned x, int max_print_bits);
void print_binary(unsigned x, int max_print_bits);

int main(void)
{
    printf("%d\n\n", count_bits(104, 8));
    printf("%d\n\n", count_bits(255, 8));
    printf("%d\n\n", count_bits((unsigned)~0, 32));
}

int count_bits(unsigned x, int max_print_bits)
{
    printf("x:\t\t");
    print_binary(x, max_print_bits);
    printf("\n");

    // x-1 flips all bits right of the rightmost 1-bit (inclusive)
    // x &= (x-1) results in 0s for all bits in this range
    // process is repeated until x = 0
    // number of iterations is number of 1-bits

    int n = 0;
    while (x > 0)
    {
        printf("iteration %d:\t", ++n);
        x &= (x - 1);
        print_binary(x, max_print_bits);
    }
    printf("\n");
    return n;
}

void print_binary(unsigned x, int max_print_bits)
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
