/*
    clean input

    remove leading and trailing whitespace
    collapse whitespace
    print non-whitespace lines
*/

#include <stdbool.h>
#include <stdio.h>

int whitespace(char ch);
int newline(char ch);

int main(void) {
    bool ch_printed = false, in_whitespace = false;
    for (int ch; (ch = getchar()) != EOF;) {
        if (whitespace((char)ch)) {
            if (!ch_printed)
                continue;
            in_whitespace = true;
        } else {
            if (newline((char)ch)) {
                if (ch_printed)
                    putchar('\n');
                ch_printed = in_whitespace = false;
            } else {
                if (in_whitespace)
                    putchar(' ');
                putchar(ch);
                ch_printed = true;
                in_whitespace = false;
            }
        }
    }
}

int whitespace(char ch) {
    return ch == ' ' || ch == '\t';
}

int newline(char ch) {
    return ch == '\n';
}
