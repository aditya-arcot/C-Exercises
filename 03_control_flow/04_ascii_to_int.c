// convert ASCII integer string to integer

#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);

int main(void)
{
    char s[] = " -123a4";
    printf("%d\n", atoi(s));
}

int atoi(char s[])
{
    int i, sign, n;

    // skip leading space
    for (i = 0; isspace(s[i]); ++i)
        ;

    // sign
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        ++i;

    // digits
    for (n = 0; isdigit(s[i]); ++i)
        n = (n * 10) + (s[i] - '0');
    return sign * n;
}
