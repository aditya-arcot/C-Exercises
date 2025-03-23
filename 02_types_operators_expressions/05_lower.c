// convert ASCII string to lower case

#include <stdio.h>

void lower(char s[]);

int main(void) {
    char s[] = "Hello, World!";
    lower(s);
    printf("%s\n", s);
}

void lower(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        // if (s[i] >= 'A' && s[i] <= 'Z')
        //     s[i] = s[i] - 'A' + 'a';

        // rewritten using conditional expr
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] - 'A' + 'a' : s[i];
    }
}
