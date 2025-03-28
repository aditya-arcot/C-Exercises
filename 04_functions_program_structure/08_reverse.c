// recursively reverse string in place

#include <stdio.h>
#include <string.h>

void run_reverse(char s[]);
void reverse(char s[], int left, int right);

int main(void) {
    char s[] = "abcde";
    run_reverse(s);
}

void run_reverse(char s[]) {
    printf("%s -> ", s);
    reverse(s, 0, (int)strlen(s) - 1);
    printf("%s\n", s);
}

void reverse(char s[], int left, int right) {
    char temp;

    if (left >= right)
        return;

    temp = s[left];
    s[left] = s[right];
    s[right] = temp;

    reverse(s, left + 1, right - 1);
}
