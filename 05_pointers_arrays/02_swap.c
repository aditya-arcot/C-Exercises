#include "debug_print.h"

void swap(int *px, int *py);

int main(void) {
    int x = 5, y = 10;

    PRINT_INT(x);
    PRINT_INT(y);

    swap(&x, &y);

    PRINT_INT(x);
    PRINT_INT(y);
}

void swap(int *px, int *py) {
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
