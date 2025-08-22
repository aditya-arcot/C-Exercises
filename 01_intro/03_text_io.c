// print input characters separated by spaces

#include <stdio.h>

int main(void) {
    printf("Enter characters (end using Ctrl+D):\n");
    for (int ch; (ch = getchar()) != EOF;) {
        putchar(ch);
        if (ch != '\n')
            putchar(' ');
    }
    putchar('\n');
}
