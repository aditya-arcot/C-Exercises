// print counts of lines, blanks, and tabs from input

#include <stdio.h>

int main(void)
{
    int ch, blanks, tabs, lines;
    blanks = tabs = lines = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ')
            ++blanks;
        else if (ch == '\t')
            ++tabs;
        else if (ch == '\n')
            ++lines;
    }

    printf("%d lines, %d blanks, %d tabs\n", lines, blanks, tabs);
}
