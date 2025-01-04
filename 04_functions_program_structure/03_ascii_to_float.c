/*
    convert ASCII double string to double

    optional sign
    optional decimal portion
    optional exponent portion with optional sign
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

double atof(char s[]);

int main(void)
{
    char s[] = " -1234.123e-2 ";
    printf("%f\n", atof(s));
}

double atof(char s[])
{
    int i, exp;
    bool neg, neg_exp;
    double n, multiplier;

    // skip leading space
    for (i = 0; isspace(s[i]); ++i)
        ;

    // store sign
    neg = s[i] == '-';
    if (s[i] == '+' || s[i] == '-')
        ++i;

    // digits before decimal
    for (n = 0; isdigit(s[i]); ++i)
        n = (n * 10) + (s[i] - '0');

    // decimal
    multiplier = 1;
    if (s[i] == '.')
    {
        i++;
        for (; isdigit(s[i]); ++i)
        {
            n = (n * 10) + (s[i] - '0');
            multiplier /= 10;
        }
    }

    // exponent
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;

        // exponent sign
        neg_exp = s[i] == '-';
        if (s[i] == '-' || s[i] == '+')
            ++i;

        for (exp = 0; isdigit(s[i]); ++i)
            exp = (exp * 10) + (s[i] - '0');

        while (exp > 0)
        {
            --exp;
            if (neg_exp)
                multiplier /= 10;
            else
                multiplier *= 10;
        }
    }

    return (neg ? -1 : 1) * n * multiplier;
}
