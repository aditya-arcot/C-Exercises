// convert integer to left-padded ASCII integer string

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NULL_CHAR '\0'

void run_itoa(int n, char s[], int min_width);
void itoa(int n, char s[], int min_width);
int abs(int n);
void reverse(char s[]);

int main(void) {
    char s[100];
    run_itoa(-128, s, 4);
    run_itoa(0, s, 2);
    run_itoa(145, s, 5);
    run_itoa(-1, s, 3);
    // -2147483647
    run_itoa((int)(1U << 31) + 1, s, 11);
    // -2147483648
    run_itoa((int)(1U << 31), s, 12);
}

void run_itoa(int n, char s[], int min_width) {
    itoa(n, s, min_width);
    printf("%12d -> %s\n", n, s);
}

void itoa(int n, char s[], int min_width) {
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

int abs(int n) {
    if (n < 0)
        return -n;
    return n;
}

void reverse(char s[]) {
    int i, j;
    char ch;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
