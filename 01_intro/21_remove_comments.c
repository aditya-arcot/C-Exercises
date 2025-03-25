// remove all comments from C program input

#include <stdbool.h>
#include <stdio.h>

static int ch;
static bool in_string = false;
static bool in_char = false;
static bool in_single_comment = false;
static bool in_multi_comment = false;

int handle_char(void);

int main(void) {
    while ((ch = getchar()) != EOF) {
        if (handle_char())
            break;
    }
}

int handle_char(void) {
    if (in_single_comment) {
        if (ch == '\n') {
            putchar(ch);
            in_single_comment = false;
        }
        return 0;
    }

    if (in_multi_comment) {
        if (ch == '*') {
            ch = getchar();
            if (ch == EOF)
                return 1;

            if (ch == '/') {
                in_multi_comment = false;
                return 0;
            }
        }
        return 0;
    }

    if (ch == '"') {
        in_string = !in_string;
        putchar(ch);
        return 0;
    }

    if (in_string) {
        putchar(ch);
        return 0;
    }

    if (ch == '\'') {
        in_char = !in_char;
        putchar(ch);
        return 0;
    }

    if (in_char) {
        putchar(ch);
        return 0;
    }

    if (ch == '/') {
        int prev_ch = ch;
        ch = getchar();
        if (ch == EOF)
            return 1;

        if (ch == '/') {
            in_single_comment = true;
            return 0;
        }

        if (ch == '*') {
            in_multi_comment = true;
            return 0;
        }

        putchar(prev_ch);
        putchar(ch);
        return 0;
    }

    putchar(ch);
    return 0;
}
