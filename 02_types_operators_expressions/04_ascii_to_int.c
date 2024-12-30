/*
    convert ASCII positive integer string to integer

    skip leading whitespace
    interpret digits until non-digit is encountered
    return integer value
*/

#include <stdio.h>
#include <stdbool.h>

int atoi(char s[]);
int is_whitespace(int ch);
int is_digit(int ch);

int main(void)
{
    char s[] = " 123a4";
    printf("%d\n", atoi(s));
}

int atoi(char s[])
{
    bool start = true;
    int n = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (is_whitespace(s[i]))
        {
            if (start)
                continue;
            else
                return n;
        }
        start = false;

        if (!is_digit(s[i]))
            return n;

        n = n * 10 + (s[i] - '0');
    }

    return n;
}

int is_whitespace(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int is_digit(int ch)
{
    return ch >= '0' && ch <= '9';
}
