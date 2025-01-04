// find index of rightmost occurence of substring

#include <stdio.h>

#define NULL_CHAR '\0'

int find_rightmost_substring_idx(char str[], char substr[]);

int main(void)
{
    char str[] = "abc abc";
    char substr[] = "ab";
    printf("%d\n", find_rightmost_substring_idx(str, substr));
}

int find_rightmost_substring_idx(char str[], char substr[])
{
    int i, j, k, pos = -1;
    // iterate over string characters
    for (i = 0; str[i] != NULL_CHAR; i++)
    {
        // check characters match until end of either string
        for (j = i, k = 0; str[j] != NULL_CHAR && substr[k] != NULL_CHAR && str[j] == substr[k]; j++, k++)
            ;
        if (substr[k] == NULL_CHAR)
            // substring found
            pos = i;
    }
    return pos;
}
