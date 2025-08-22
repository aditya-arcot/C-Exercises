// print input words separated by newlines

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    bool in_word = false;
    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (in_word)
                putchar('\n');
            in_word = false;
        } else {
            putchar(ch);
            in_word = true;
        }
    }
    putchar('\n');
}
