/*
    unescape newline and tab visible sequences into characters
    while copying string in to out
*/

#include <stdio.h>

#define NULL_CHAR '\0'

void unescape(char in[], char out[]);

int main(void) {
    char in[] = "abc\\t123\\ntest";
    char out[100];
    unescape(in, out);
    printf("%s\n", out);
}

void unescape(char in[], char out[]) {
    int i, j;
    for (i = j = 0; in[i] != NULL_CHAR; i++) {
        switch (in[i]) {
        case '\\':
            switch (in[++i]) {
            case 'n':
                out[j++] = '\n';
                break;
            case 't':
                out[j++] = '\t';
                break;
            default:
                out[j++] = '\\';
                out[j++] = in[i];
                break;
            }
            break;
        default:
            out[j++] = in[i];
            break;
        }
    }
    out[j] = NULL_CHAR;
}
