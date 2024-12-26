// reverse and print each line of input

#include <stdio.h>

#define MAX_LINE 10
#define NULL_CHAR '\0'

int get_line(char line[], int max_line_len);
void reverse(char line[], int len);

int main(void)
{
    int len = 0;
    char line[MAX_LINE + 1];
    while ((len = get_line(line, MAX_LINE)) > 0)
        reverse(line, len);
}

int get_line(char line[], int max_line_len)
{
    int ch, col = 0;
    while ((ch = getchar()) != EOF)
    {
        ++col;
        if (ch == '\n')
            break;
        if (col < max_line_len)
            line[col] = ch;
    }
    line[max_line_len] = NULL_CHAR;
    return col;
}

void reverse(char line[], int len)
{
    for (int i = len - 1; i >= 0; --i)
        putchar(line[i]);
    putchar('\n');
}
