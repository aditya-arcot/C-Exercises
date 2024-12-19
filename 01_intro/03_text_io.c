// print input characters separated by spaces

#include <stdio.h>

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