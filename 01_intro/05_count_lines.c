// print input line count

#include <stdio.h>

int main(void) {
    int lines = 0;
    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == '\n')
            ++lines;
    }
    printf("%d lines\n", lines);
}
