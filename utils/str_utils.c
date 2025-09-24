#include "str_utils.h"
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

/*
copies string s to string t
from 05_pointers_arrays/07_str_copy.c

params:
    s - source string
    t - destination string
*/
void str_copy(char *s, char *t) {
    while ((*t++ = *s++))
        ;
}

char lower(char s) {
    return (s >= 'A' && s <= 'Z') ? s - 'A' + 'a' : s;
}

int char_diff(char a, char b, bool fold) {
    if (fold)
        return lower(a) - lower(b);
    return a - b;
}

/*
compares string s to string t
from 05_pointers_arrays/08_str_cmp.c

params:
    s - first string
    t - second string
    fold - if true, ignore case differences

returns:
    <0 if s<t
    0 if s==t
    >0 if s>t
*/
int str_cmp(char *s, char *t, bool fold) {
    for (; char_diff(*s, *t, fold) == 0; s++, t++)
        if (!*s)
            return 0;
    return char_diff(*s, *t, fold);
}

/*
concats string s to end of string t
from 05_pointers_arrays/09_str_cat.c

params:
    s - source string
    t - destination string
*/
void str_cat(char *s, char *t) {
    while (*t)
        t++;
    while ((*t++ = *s++))
        ;
}
