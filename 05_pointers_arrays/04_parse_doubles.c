/*
    parse doubles from input

    format - [sign] integer_part [fractional_part] [e/E [sign] exponent]
    each double is parsed until non-allowed char is encountered
*/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 3

int get_dbl(double *pn);

int main(void) {
    double arr[SIZE];
    int n, res;

    for (n = 0; n < SIZE && (res = get_dbl(&arr[n])) != EOF;) {
        if (res > 0)
            n++;
    }

    for (int i = 0; i < n; ++i)
        printf("%f ", arr[i]);
    printf("\n");
}

// get next dbl from input into *pn
int get_dbl(double *pn) {
    int ch, n, power, exp, sign, exp_sign;

    while (isspace(ch = getchar()))
        ;

    if (ch == EOF)
        return EOF;
    if (ch != '+' && ch != '-' && !isdigit(ch))
        return 0;

    sign = (ch == '-') ? -1 : 1;
    if (ch == '+' || ch == '-') {
        ch = getchar();
        if (!isdigit(ch))
            return 0;
    }

    // integer part
    for (n = 0; isdigit(ch); ch = getchar())
        n = (n * 10) + (ch - '0');

    // fractional part
    power = 0;
    if (ch == '.') {
        if (!isdigit(ch = getchar()))
            return 0;
        for (; isdigit(ch); ch = getchar()) {
            n = (n * 10) + (ch - '0');
            --power;
        }
    }

    // exponent
    if (ch == 'e' || ch == 'E') {
        ch = getchar();

        exp_sign = (ch == '-') ? -1 : 1;
        if (ch == '-' || ch == '+') {
            ch = getchar();
        }

        if (!isdigit(ch))
            return 0;
        for (exp = 0; isdigit(ch); ch = getchar())
            exp = (exp * 10) + (ch - '0');

        power += (exp_sign == -1) ? -1 * exp : exp;
    }

    *pn = sign * n * pow(10, power);
    return 1;
}
