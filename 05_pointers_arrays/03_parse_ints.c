/*
    parse integers from input

    optional sign
    each integer is parsed until non-digit is encountered
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 3

int get_int(int *pn);

int main(void) {
    int arr[SIZE], n, res;

    for (n = 0; n < SIZE && (res = get_int(&arr[n])) != EOF;) {
        if (res > 0)
            n++;
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// get next int from input into *pn
int get_int(int *pn) {
    int ch, sign;

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

    for (*pn = 0; isdigit(ch); ch = getchar())
        *pn = (*pn * 10) + (ch - '0');
    *pn *= sign;
    return 1;
}
