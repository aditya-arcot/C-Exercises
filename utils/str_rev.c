#include "str_rev.h"
#include <string.h>

/*
reverses string s in place
from 03_control_flow/05_reverse.c

params:
    s - string to reverse
*/
void str_rev(char s[]) {
    int i, j;
    char ch;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
