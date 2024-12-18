#include <stdio.h>

// collapse whitespace into single space

#define TRUE 1
#define FALSE 0

int main()
{
    int ch, in_blank = FALSE;

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\t')
        {
            if (!in_blank)
                putchar(' ');
            in_blank = TRUE;
        }
        else
        {
            putchar(ch);
            in_blank = FALSE;
        }
    }

    putchar('\n');
}