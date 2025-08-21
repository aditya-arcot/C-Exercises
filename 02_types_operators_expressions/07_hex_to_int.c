/*
    convert ASCII positive hexadecimal string to integer

    allow leading 0x or 0X
    interpret digits until non-hex digit encountered
    return integer value
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int htoi(char s[]);
int is_whitespace(int ch);

int main(void) {
    char s[] = "0x1f";
    printf("%s - %d\n", s, htoi(s));

    char s2[] = " FF";
    printf("%s - %d\n", s2, htoi(s2));

    char s3[] = "052";
    printf("%s - %d\n", s3, htoi(s3));
}

int htoi(char s[]) {
    int i = 0, n = 0;

    // strip leading whitespace
    while (is_whitespace(s[i]))
        i++;

    // strip hex prefix
    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
        i += 2;
    }

    // parse hex digits
    for (int ch; (ch = s[i++]) != '\0';) {
        if (!isxdigit(ch))
            break;
        if (ch >= '0' && ch <= '9')
            n = n * 16 + (ch - '0');
        else if (ch >= 'a' && ch <= 'f')
            n = n * 16 + (ch - 'a' + 10);
        else
            n = n * 16 + (ch - 'A' + 10);
    }
    return n;
}

int is_whitespace(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}
