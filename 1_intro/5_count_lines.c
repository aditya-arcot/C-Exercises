#include <stdio.h>

int main()
{
    int ch, lines;

    lines = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
            lines++;
    }

    printf("%d lines\n", lines);
}