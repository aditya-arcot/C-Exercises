// recursively print number as character string

#include <stdio.h>

void run_print_int(int n);
void print_int(int n);
int abs(int n);

int main(void) {
    run_print_int(123);
    run_print_int(-123);
    // -2147483647
    run_print_int((int)(1U << 31) + 1);
    // -2147483648
    run_print_int((int)(1U << 31));
}

void run_print_int(int n) {
    printf("%d -> ", n);
    print_int(n);
    printf("\n");
}

void print_int(int n) {
    if (n < 0)
        putchar('-');
    if (n / 10)
        print_int(abs(n / 10));
    putchar('0' + (char)abs(n % 10));
}

int abs(int n) {
    if (n < 0)
        return -n;
    return n;
}
