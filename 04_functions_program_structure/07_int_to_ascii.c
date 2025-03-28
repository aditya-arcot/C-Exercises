// recursively convert integer to ASCII integer string

#include <stdio.h>

#define NULL_CHAR '\0'

void run_itoa(int n, char s[]);
void itoa(int n, char s[]);
int abs(int n);

int main(void) {
    char s[100];
    run_itoa(-128, s);
    run_itoa(0, s);
    run_itoa(145, s);
    run_itoa(-1, s);
    // -2147483647
    run_itoa((int)(1U << 31) + 1, s);
    // -2147483648
    run_itoa((int)(1U << 31), s);
}

void run_itoa(int n, char s[]) {
    itoa(n, s);
    printf("%d -> %s\n", n, s);
}

void itoa(int n, char s[]) {
    static int idx;
    if (n / 10)
        itoa(n / 10, s);
    else {
        idx = 0;
        if (n < 0)
            s[idx++] = '-';
    }
    s[idx++] = '0' + (char)abs(n % 10);
    s[idx] = NULL_CHAR;
}

int abs(int n) {
    if (n < 0)
        return -n;
    return n;
}
