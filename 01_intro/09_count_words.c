// print input word count

#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(void)
{
    int ch, in_word = FALSE, words = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
            in_word = FALSE;
        }
        else if (!in_word)
        {
            ++words;
            in_word = TRUE;
        }
    }

    printf("%d words\n", words);
}
