// print input with whitespace collapsed

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int ch;
    bool in_blank = false;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (!in_blank)
                putchar(' ');
            in_blank = true;
        } else {
            putchar(ch);
            in_blank = false;
        }
    }

    putchar('\n');
}
