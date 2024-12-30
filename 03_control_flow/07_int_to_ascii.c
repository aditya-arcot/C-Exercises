// convert integer to ASCII integer string

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NULL_CHAR '\0'

void itoa(int n, char s[], int min_width);
int abs(int n);
void reverse(char s[]);

int main(void)
{
    char s[100];

    itoa(-128, s, 5);
    printf("%s\n", s);

    itoa(0, s, 5);
    printf("%s\n", s);

    itoa(145, s, 5);
    printf("%s\n", s);

    itoa(-1, s, 5);
    printf("%s\n", s);

    // -2147483647
    itoa((1 << 31) + 1, s, 12);
    printf("%s\n", s);

    // -2147483648
    itoa(1 << 31, s, 12);
    printf("%s\n", s);
}

void itoa(int n, char s[], int min_width)
{
    // record sign
    bool negative = (n < 0);

    // add chars to string in reverse order
    int i = 0;
    do
        s[i++] = '0' + (char)abs(n % 10);
    while ((n /= 10) != 0);

    // add negative sign
    if (negative)
        s[i++] = '-';

    while (i < min_width)
        s[i++] = ' ';

    // null-terminate string
    s[i] = NULL_CHAR;

    // reverse string
    reverse(s);
}

int abs(int n)
{
    if (n < 0)
        return -n;
    return n;
}

void reverse(char s[])
{
    int i, j;
    char ch;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--)
    {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
