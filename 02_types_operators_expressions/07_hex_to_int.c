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
int recalculate_int(int curr, int xdigit);

int main(void) {
    char s[] = "0x1f";
    printf("%s - %d\n", s, htoi(s));

    char s2[] = " FF";
    printf("%s - %d\n", s2, htoi(s2));
}

int htoi(char s[]) {
    bool start = true;

    int n = 0;
    bool prefix = true;
    for (int i = 0; s[i] != EOF; i++) {
        if (is_whitespace(s[i])) {
            if (start)
                continue;
            else
                return n;
        }
        start = false;

        if (prefix) {
            prefix = false;
            if (s[i] == '0') {
                ++i;
                if (s[i] == 'x' || s[i] == 'X')
                    continue;
                if (!isxdigit(s[i]))
                    return n;
                n = recalculate_int(n, s[i]);
                continue;
            }
            if (!isxdigit(s[i]))
                return n;
            n = recalculate_int(n, s[i]);
            continue;
        }
        if (!isxdigit(s[i]))
            return n;
        n = recalculate_int(n, s[i]);
    }
    return n;
}

int is_whitespace(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int recalculate_int(int curr, int xdigit) {
    if (!isxdigit(xdigit))
        return curr;
    if (xdigit >= '0' && xdigit <= '9')
        return curr * 16 + (xdigit - '0');
    if (xdigit >= 'a' && xdigit <= 'f')
        return curr * 16 + (xdigit - 'a' + 10);
    return curr * 16 + (xdigit - 'A' + 10);
}
