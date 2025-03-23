// remove all characters from s1 that are in s2

#include <stdio.h>

void filter(char s1[], char s2[]);

int main(void) {
    char s1[] = "hello, world!";
    char s2[] = "aeiou";
    filter(s1, s2);
    printf("%s\n", s1);
}

void filter(char s1[], char s2[]) {
    int i, j, k;
    for (i = k = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++)
            ;
        if (s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}
