/*
    convert ASCII hexadecimal string to integer

    optional leading 0x or 0X
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int htoi(char s[]);
int calculate_int(int n, int hex);

int main(void)
{
    char s[] = "0x1f";
    printf("%s - %d\n", s, htoi(s));

    char s2[] = "FF";
    printf("%s - %d\n", s2, htoi(s2));
}

int htoi(char s[])
{
    int n = 0;
    bool prefix = true;
    for (int i = 0; s[i] != EOF; i++)
    {
        int ch = s[i];
        if (prefix)
        {
            prefix = false;
            if (s[i] == '0')
            {
                ch = s[++i];
                if (ch == 'x' || ch == 'X')
                    continue;
                if (!isxdigit(ch))
                    return n;
                n = calculate_int(n, ch);
                continue;
            }
            if (!isxdigit(ch))
                return n;
            n = calculate_int(n, ch);
            continue;
        }
        if (!isxdigit(ch))
            return n;
        n = calculate_int(n, ch);
    }
    return n;
}

int calculate_int(int n, int hex)
{
    if (!isxdigit(hex))
        return n;
    if (hex >= '0' && hex <= '9')
        return n * 16 + (hex - '0');
    if (hex >= 'a' && hex <= 'f')
        return n * 16 + (hex - 'a' + 10);
    return n * 16 + (hex - 'A' + 10);
}
