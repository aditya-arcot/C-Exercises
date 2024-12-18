#include <stdio.h>

// count digits, whitespace, and other characters

int main()
{
    int ch, n_digit[10], n_white, n_other;

    n_white = n_other = 0;
    for (int i = 0; i < 10; i++)
        n_digit[i] = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch >= '0' && ch <= '9')
            n_digit[ch - '0']++;
        else if (ch == ' ' || ch == '\t' || ch == '\n')
            n_white++;
        else
            n_other++;
    }

    printf("digits: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", n_digit[i]);
    printf("\nwhite: %d\nother: %d\n", n_white, n_other);
}