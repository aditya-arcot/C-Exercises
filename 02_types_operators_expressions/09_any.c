// find first location in s1 where a character from s2 occurs

#include <stdio.h>

int any(char s1[], char s2[]);

int main(void) {
    char s1[] = "hello, world!";
    char s2[] = "io l";
    printf("%d\n", any(s1, s2));
}

int any(char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;
    }
    return -1;
}
