// concat string t to end of string s

#include "debug_print.h"

void str_cat(char *s, char *t);

int main(void) {
    char s[] = "World!";
    char t[50] = "Hello ";
    PRINT_STR(s);
    PRINT_STR(t);
    str_cat(s, t);
    PRINT_STR(t);
}

void str_cat(char *s, char *t) {
    while (*t)
        t++;
    while ((*t++ = *s++))
        ;
}
