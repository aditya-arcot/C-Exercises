// replace input tabs with spaces

#include <stdio.h>

#define TAB_WIDTH 4

void print_spaces(int n);

int main(void) {
    int col = 0;
    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == '\t') {
            // print spaces till next tab stop
            int spaces = TAB_WIDTH - (col % TAB_WIDTH);
            print_spaces(spaces);
            col += spaces;
        } else {
            putchar(ch);
            ++col;
            if (ch == '\n') {
                col = 0;
            }
        }
    }
}

void print_spaces(int n) {
    while ((n--) > 0)
        putchar(' ');
}
