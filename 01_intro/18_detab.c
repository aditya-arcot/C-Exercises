// replace input tabs with spaces

#include <stdio.h>

#define TAB_WIDTH 4

void print_spaces(int n);

int main(void) {
    int ch, col = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '\t') {
            // print spaces till next tab stop
            int spaces = TAB_WIDTH - (col % TAB_WIDTH);
            print_spaces(spaces);
            col += spaces;
        } else {
            putchar(ch);
            if (ch == '\n') {
                col = 0;
            } else {
                ++col;
            }
        }
    }
}

void print_spaces(int n) {
    while (n > 0) {
        putchar(' ');
        --n;
    }
}
