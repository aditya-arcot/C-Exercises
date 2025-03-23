// replace input spaces with tabs

#include <stdio.h>

#define TAB_WIDTH 4

void print_spaces(int n);

int main(void) {
    int ch, col, spaces;
    col = spaces = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ') {
            ++col;
            ++spaces; // buffer space
        } else {
            if (spaces > 0) {
                // entab buffered spaces
                int next_tab_spaces = TAB_WIDTH - ((col - spaces) % TAB_WIDTH);
                if (spaces < next_tab_spaces) {
                    // not enough spaces for tab
                    print_spaces(spaces);
                } else {
                    while (spaces >= next_tab_spaces) {
                        // print tab
                        putchar('\t');
                        spaces -= next_tab_spaces;
                        next_tab_spaces = TAB_WIDTH;
                    }
                    // print remaining spaces
                    print_spaces(spaces);
                }
                spaces = 0;
            }

            // print non-space char
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
