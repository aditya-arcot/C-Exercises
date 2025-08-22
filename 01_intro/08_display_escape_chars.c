// print input with escape sequences displayed

#include <stdio.h>

int main(void) {
    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == '\t')
            printf("<\\t>");
        else if (ch == '\b')
            printf("<\\b>");
        else if (ch == '\\')
            printf("<\\\\>");
        else
            putchar(ch);
    }
    putchar('\n');
}
