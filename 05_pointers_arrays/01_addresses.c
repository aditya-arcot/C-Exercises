#include "debug_print.h"

int main(void) {
    int x = 1, y = 2;

    PRINT_INT(x);
    PRINT_INT(y);

    // int pointer
    int *p;
    // point p to x
    p = &x;
    // set y to 1
    y = *p;
    // set x to 0
    *p = 0;

    PRINT_INT(x);
    PRINT_INT(y);
}
