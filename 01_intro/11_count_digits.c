// print counts of digits, whitespace, and other characters from input

#include <stdio.h>

int main()
{
    int ch, n_digit[10], n_white, n_other;

    n_white = n_other = 0;
    for (int i = 0; i < 10; ++i)
        n_digit[i] = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch >= '0' && ch <= '9')
            ++n_digit[ch - '0'];
        else if (ch == ' ' || ch == '\t' || ch == '\n')
            ++n_white;
        else
            ++n_other;
    }

    printf("digits: ");
    for (int i = 0; i < 10; ++i)
        printf("%d ", n_digit[i]);
    printf("\n");
    printf("white: %d\n", n_white);
    printf("other: %d\n", n_other);
}