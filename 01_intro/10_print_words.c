// print input words separated by newlines

#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(void)
{
    int ch, in_word = FALSE;

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
            if (in_word)
                putchar('\n');
            in_word = FALSE;
        }
        else
        {
            putchar(ch);
            in_word = TRUE;
        }
    }

    putchar('\n');
}
