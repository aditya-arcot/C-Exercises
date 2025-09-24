// compare two strings

#include "debug_print.h"

int str_cmp(char *s, char *t);

int main(void) {
    char s1[] = "test";
    char s2[] = "test";
    char s3[] = "test2";
    PRINT_STR(s1);
    PRINT_STR(s2);
    PRINT_STR(s3);
    PRINT_INT(str_cmp(s1, s2));
    PRINT_INT(str_cmp(s1, s3));
    PRINT_INT(str_cmp(s3, s1));
}

// array version
// int str_cmp(char *s, char *t) {
//     int i;
//     for (i = 0; s[i] == t[i]; i++)
//         // equivalent to: if (s[i] == '\0')
//         if (!s[i])
//             return 0;
//     return s[i] - t[i];
// }

// pointer version
int str_cmp(char *s, char *t) {
    for (; *s == *t; s++, t++)
        if (!*s)
            return 0;
    return *s - *t;
}
