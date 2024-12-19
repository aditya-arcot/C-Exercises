/*
    clean input

    remove leading and trailing whitespace
    collapse whitespace
    print non-whitespace lines
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0

int whitespace(char ch) { return ch == ' ' || ch == '\t'; }
int newline(char ch) { return ch == '\n'; }

int main()
{
    int ch;
    int ch_printed, in_whitespace;
    ch_printed = in_whitespace = FALSE;

    while ((ch = getchar()) != EOF)
    {
        if (whitespace(ch))
        {
            if (!ch_printed)
                continue;
            in_whitespace = TRUE;
        }
        else
        {
            if (newline(ch))
            {
                if (ch_printed)
                    putchar('\n');
                ch_printed = in_whitespace = FALSE;
            }
            else
            {
                if (in_whitespace)
                    putchar(' ');
                putchar(ch);
                ch_printed = TRUE;
                in_whitespace = FALSE;
            }
        }
    }
}
