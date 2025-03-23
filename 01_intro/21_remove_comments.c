// remove all comments from C program input

#include <stdio.h>

#define TRUE 1
#define FALSE 0

int ch = -1;

int in_string = FALSE;
int in_char = FALSE;
int in_single_comment = FALSE;
int in_multi_comment = FALSE;
int escaped = FALSE;

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
            in_single_comment = FALSE;
        }
        return 0;
    }

    if (in_multi_comment) {
        if (ch == '*') {
            ch = getchar();
            if (ch == EOF)
                return 1;

            if (ch == '/') {
                in_multi_comment = FALSE;
                return 0;
            }
        }
        return 0;
    }

    if (escaped) {
        escaped = FALSE;
        putchar(ch);
        return 0;
    }

    if (ch == '\\') {
        escaped = TRUE;
        putchar(ch);
        return 0;
    }

    if (ch == '"' && !escaped) {
        in_string = !in_string;
        putchar(ch);
        return 0;
    }

    if (in_string) {
        putchar(ch);
        return 0;
    }

    if (ch == '\'' && !escaped) {
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
            in_single_comment = TRUE;
            return 0;
        }

        if (ch == '*') {
            in_multi_comment = TRUE;
            return 0;
        }

        putchar(prev_ch);
        putchar(ch);
        return 0;
    }

    putchar(ch);
    return 0;
}
