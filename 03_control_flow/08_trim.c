// trim trailing space

#define NULL_CHAR '\0'

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void trim_trailing(char s[]);

int main(void) {
    char s[] = "abc d \n\t";
    trim_trailing(s);
    printf("%s\n", s);
}

void trim_trailing(char s[]) {
    int i;
    for (i = (int)strlen(s) - 1; i >= 0; i--) {
        if (!isspace(s[i]))
            break;
    }
    s[i + 1] = NULL_CHAR;
}
