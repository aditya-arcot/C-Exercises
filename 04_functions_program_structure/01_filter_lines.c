// print each line of input that contains a string

#include <stdio.h>

#define MAX_LINE 5
#define NULL_CHAR '\0'

int get_line(char line[], int max);
int find_substring_idx(char str[], char substr[]);

int main(void)
{
    char line[MAX_LINE + 1]; // 1 extra for null terminator
    char pattern[] = "abc";

    // while not EOF
    while (get_line(line, MAX_LINE) != EOF)
    {
        // skip empty line
        if (line[0] == NULL_CHAR)
            continue;

        // if substring found
        if (find_substring_idx(line, pattern) != -1)
            // print line
            printf("%s\n", line);
    }
}

int get_line(char line[], int max)
{
    int ch, i;
    ch = i = 0;

    // store characters until max length, EOF, or newline
    while (max-- > 0 && (ch = getchar()) != EOF && ch != '\n')
        line[i++] = (char)ch;

    // EOF with no characters read
    if (i == 0 && ch == EOF)
        return EOF;

    // null terminate
    line[i] = NULL_CHAR;

    // skip remaining characters in line
    if (max < 0)
        while ((ch = getchar()) != EOF && ch != '\n')
            ;

    // return length
    return i;
}

int find_substring_idx(char str[], char substr[])
{
    int i, j, k;
    // iterate over string characters
    for (i = 0; str[i] != NULL_CHAR; i++)
    {
        // check characters match until end of either string
        for (j = i, k = 0; str[j] != NULL_CHAR && substr[k] != NULL_CHAR && str[j] == substr[k]; j++, k++)
            ;
        if (substr[k] == NULL_CHAR)
            // substring found
            return i;
    }
    return -1;
}
