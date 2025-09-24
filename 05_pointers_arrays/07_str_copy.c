// copy string s to string t

#include "debug_print.h"

void str_copy(char *s, char *t);

int main(void) {
    char s[] = "Hello, World!";
    char t[50];
    PRINT_STR(s);
    PRINT_STR(t);
    str_copy(s, t);
    PRINT_STR(t);
}

// array version
// void str_copy(char *s, char *t) {
//     int i;
//     i = 0;
//     // equivalent to: while ((t[i] = s[i]) != '\0')
//     while ((t[i] = s[i]))
//         i++;
// }

// pointer version
void str_copy(char *s, char *t) {
    while ((*t++ = *s++))
        ;
}
