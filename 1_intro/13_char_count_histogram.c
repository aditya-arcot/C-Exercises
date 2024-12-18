#include <stdio.h>

// vertical histogram of printable ASCII characters

#define MINCHAR 33
#define MAXCHAR 126

int main()
{
    int ch, max_count = 0;
    int counts[MAXCHAR - MINCHAR + 1];

    for (int i = 0; i < MAXCHAR - MINCHAR + 1; i++)
        counts[i] = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch >= MINCHAR && ch <= MAXCHAR)
        {
            counts[ch - MINCHAR]++;
            if (counts[ch - MINCHAR] > max_count)
                max_count = counts[ch - MINCHAR];
        }
    }

    // horizontal histogram
    // printf("\nCharacter Histogram\n");
    // for (int i = 0; i < MAXCHAR - MINCHAR + 1; i++)
    // {
    //     printf("%c: ", MINCHAR + i);
    //     for (int j = 0; j < counts[i]; j++)
    //         printf("=");
    //     printf("\n");
    // }
    // printf("\n");

    // vertical histogram
    printf("\nCharacter Histogram\n");
    for (int i = max_count; i > 0; i--)
    {
        for (int j = 0; j < MAXCHAR - MINCHAR + 1; j++)
        {
            if (counts[j] >= i)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
    for (int i = 0; i < MAXCHAR - MINCHAR + 1; i++)
    {
        printf("==");
    }
    printf("\n");
    for (int i = 0; i < MAXCHAR - MINCHAR + 1; i++)
    {
        printf("%c ", MINCHAR + i);
    }
    printf("\n\n");
}