// convert integer n into base b character representation in string s

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NULL_CHAR '\0'

void run_itob(int n, char s[], int base);
void itob(int n, char s[], int base);
int abs(int n);
void reverse(char s[]);

int main(void) {
    char s[100];
    run_itob(-255, s, 16);
    run_itob(1024, s, 8);
    run_itob(-5, s, 2);
    run_itob((int)(1U << 31) + 1, s, 2);
    run_itob((int)(1U << 31), s, 2);
}

void run_itob(int n, char s[], int base) {
    itob(n, s, base);
    printf("%d to base %d -> %s\n", n, base, s);
}

void itob(int n, char s[], int base) {
    // record sign
    bool negative = (n < 0);

    // add chars to string in reverse order
    int i = 0, r;
    do {
        r = abs(n) % base;
        s[i++] = (r < 10) ? (char)r + '0' : (char)r - 10 + 'A';
    } while (abs(n /= base) != 0);

    // add negative sign
    if (negative)
        s[i++] = '-';

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
    for (int i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        char ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
