#include <stdio.h>

// print characters separated by spaces

int main()
{
    int c;
    printf("Enter characters (end using Ctrl+D):\n");
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        if (c != '\n')
            putchar(' ');
    }
    putchar('\n');
}