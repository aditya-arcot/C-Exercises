/*
    expand shorthand notations like a-z in string s1 into
    equivalent complete list abc...xyz in s2
*/

#include <stdio.h>

#define NULL_CHAR '\0'

void expand(char s1[], char s2[]);

int main(void) {
    char s1[] = "a-f f-a 0-5 5-0 a-b-c-e-z --0";
    char s2[128];
    expand(s1, s2);
    printf("%s\n", s2);
}

void expand(char s1[], char s2[]) {
    int i = 0, j = 0;
    for (int ch; (ch = s1[i++]) != NULL_CHAR;) {
        if (s1[i] == '-' && s1[i + 1] >= ch) {
            while (ch <= s1[i + 1])
                s2[j++] = ch++;
            i += 2;
        } else
            s2[j++] = ch;
    }
    s2[j] = NULL_CHAR;
}
