// print powers table

#include <stdio.h>

// function prototype
double power(int base, int exp);

int main(void) {
    const int range = 4;
    const int col_width = 10;

    // list of exponents
    printf("%5s", "");
    for (int i = -range; i <= range; ++i) {
        printf("%*d", col_width, i);
    }
    printf("\n");

    // separator
    printf("%5s", "");
    for (int i = 0; i <= (2 * range); ++i) {
        for (int j = 0; j < col_width; ++j) {
            printf("-");
        }
    }
    printf("\n");

    for (int i = -range; i <= range; ++i) {
        printf("%3d |", i); // base with separator
        for (int j = -range; j <= range; ++j) {
            if (i == 0 && j < 0) {
                printf("%*s", col_width, "-");
            } else {
                printf("%*.3f", col_width, power(i, j));
            }
        }
        printf("\n");
    }
}

double power(int base, int exp) {
    if (base == 0) {
        if (exp == 0)
            return 1;
        if (exp < 0) {
            printf("error - cannot raise 0 to a negative power\n");
            return -1;
        }
        return 0;
    }

    if (exp < 0)
        return 1 / power(base, -exp);

    double result = 1;
    while (exp > 0) {
        result *= base;
        --exp;
    }
    return result;
}
