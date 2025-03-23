// reverse string in place

#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(void) {
    char s[] = "abcde";
    reverse(s);
    printf("%s\n", s);
}

void reverse(char s[]) {
    int i, j;
    char ch;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
