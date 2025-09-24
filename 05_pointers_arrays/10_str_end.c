// check if string t occurs at end of string s

#include "debug_print.h"

bool str_end(char *s, char *t);

int main(void) {
    char s[] = "testing";
    char t[] = "ing";
    PRINT_STR(s);
    PRINT_STR(t);
    PRINT_BOOL(str_end(s, t));
}

bool str_end(char *s, char *t) {
    int len_s, len_t;
    char *ptr;

    for (ptr = s; *ptr; ptr++)
        ;
    len_s = ptr - s;

    for (ptr = t; *ptr; ptr++)
        ;
    len_t = ptr - t;

    if (len_t > len_s)
        return false;

    s += len_s - len_t;
    while (*s && *s == *t) {
        s++;
        t++;
    }
    return !*t;
}
