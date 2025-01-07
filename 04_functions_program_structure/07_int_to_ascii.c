// recursively convert integer to ASCII integer string

#include <stdio.h>

#define NULL_CHAR '\0'

void itoa(int n, char s[]);
int abs(int n);

int main(void)
{
    char s[100];

    itoa(-128, s);
    printf("%s\n", s);

    itoa(0, s);
    printf("%s\n", s);

    itoa(145, s);
    printf("%s\n", s);

    itoa(-1, s);
    printf("%s\n", s);

    // -2147483647
    itoa((1 << 31) + 1, s);
    printf("%s\n", s);

    // -2147483648
    itoa(1 << 31, s);
    printf("%s\n", s);
}

void itoa(int n, char s[])
{
    static int idx;
    if (n / 10)
        itoa(n / 10, s);
    else
    {
        idx = 0;
        if (n < 0)
            s[idx++] = '-';
    }
    s[idx++] = '0' + (char)abs(n % 10);
    s[idx] = NULL_CHAR;
}

int abs(int n)
{
    if (n < 0)
        return -n;
    return n;
}
