// recursively reverse string in place

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void _reverse(char s[], int left, int right);

int main(void)
{
    char s[] = "abcde";
    reverse(s);
    printf("%s\n", s);
}

void reverse(char s[])
{
    _reverse(s, 0, (int)strlen(s) - 1);
}

void _reverse(char s[], int left, int right)
{
    char temp;

    if (left >= right)
        return;

    temp = s[left];
    s[left] = s[right];
    s[right] = temp;

    _reverse(s, left + 1, right - 1);
}
