// recursively print number as character string

#include <stdio.h>

void print_int(int n);
int abs(int n);

int main(void)
{
    print_int(123);
    printf("\n");

    print_int(-123);
    printf("\n");

    // -2147483647
    print_int((1 << 31) + 1);
    printf("\n");

    // -2147483648
    print_int(1 << 31);
    printf("\n");
}

void print_int(int n)
{
    if (n < 0)
        putchar('-');
    if (n / 10)
        print_int(abs(n / 10));
    putchar('0' + (char)abs(n % 10));
}

int abs(int n)
{
    if (n < 0)
        return -n;
    return n;
}
