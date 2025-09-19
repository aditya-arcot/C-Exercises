#include "get_line.h"
#include <ctype.h>
#include <stdio.h>

#define NULL_CHAR '\0'
#define NEWLINE_CHAR '\n'

/*
reads line & returns length

params:
    line - char array of length max_len + 1
    max_len - max chars to read
    allow_overflow - if true, counts chars beyond max_len
    exclude_leading_blanks - if true, ignores leading blanks

returns:
    length of line read (excluding null char & EOF) or EOF
*/
int get_line(char line[], int max_len, bool allow_overflow, bool exclude_leading_blanks) {
    int ch, i, j;
    bool blank;
    i = 0;
    blank = true;
    while (max_len-- > 0 && (ch = getchar()) != EOF && ch != NEWLINE_CHAR) {
        if (!exclude_leading_blanks || !blank || !isblank(ch)) {
            blank = false;
            line[i++] = (char)ch;
        }
    }
    if (i == 0 && ch == EOF)
        return EOF;
    j = i;
    if (max_len < 0) {
        for (; (ch = getchar()) != EOF && ch != NEWLINE_CHAR; j++)
            ;
        printf("Warning: truncating line to %d characters\n", i);
    }
    line[i] = NULL_CHAR;
    return allow_overflow ? j : i;
}
