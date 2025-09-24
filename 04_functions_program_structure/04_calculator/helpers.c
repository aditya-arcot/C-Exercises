// Helper functions for calculator

#include "calc.h"
#include <stdbool.h>

double dbl_abs(double num) {
    if (num < 0)
        return -num;
    return num;
}

double dbl_mod(double x, double y) {
    return x - ((int)(x / y) * y);
}

bool str_eq(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return false;
        ++s1;
        ++s2;
    }
    return *s1 == NULL_CHAR && *s2 == NULL_CHAR;
}
