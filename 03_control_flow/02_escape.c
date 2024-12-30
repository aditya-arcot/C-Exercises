/*
    expand newline and tab characters into visible sequences
    while copying string in to out
*/

#include <stdio.h>

#define NULL_CHAR '\0'

void escape(char in[], char out[]);

int main(void)
{
    char in[] = "abc\t123\ntest";
    char out[100];
    escape(in, out);
    printf("%s\n", out);
}

void escape(char in[], char out[])
{
    int i, j;
    for (i = j = 0; in[i] != NULL_CHAR; i++)
    {
        switch (in[i])
        {
        case '\n':
            out[j++] = '\\';
            out[j++] = 'n';
            break;
        case '\t':
            out[j++] = '\\';
            out[j++] = 't';
            break;
        default:
            out[j++] = in[i];
            break;
        }
    }
    out[j] = NULL_CHAR;
}
