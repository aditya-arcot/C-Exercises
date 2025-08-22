// print counts of lines, blanks, and tabs from input

#include <stdio.h>

int main(void) {
    int blanks = 0, tabs = 0, lines = 0;
    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == ' ')
            ++blanks;
        else if (ch == '\t')
            ++tabs;
        else if (ch == '\n')
            ++lines;
    }
    printf("%d lines, %d blanks, %d tabs\n", lines, blanks, tabs);
}
