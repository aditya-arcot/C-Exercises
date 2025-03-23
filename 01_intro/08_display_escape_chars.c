// print input with escape sequences displayed

#include <stdio.h>

int main(void) {
    int ch;
    while ((ch = getchar()) != EOF) {
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
