#include "line_utils.h"
#include "alloc.h"
#include "str_utils.h"
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

#define MAX_LEN 1000

/*
reads lines & returns number of lines
from 05_pointers_arrays/11_str_sort.c

params:
    line_ptrs: array of string pointers to store lines
    max_lines: max number of lines to read

returns:
    number of lines read
    if too many lines, LINES_OVERFLOW (-1)
    if alloc fails, ALLOC_ERR (-2)
*/
int read_lines(char *line_ptrs[], int max_lines) {
    int len, n_lines = 0;
    char *ptr, line[MAX_LEN + 1];
    while ((len = get_line(line, MAX_LEN, false, false)) > 0) {
        if (n_lines >= max_lines)
            return LINES_OVERFLOW;
        // 1 extra for null char
        ptr = alloc(len + 1);
        if (ptr == NULL)
            return ALLOC_ERR;
        str_copy(line, ptr);
        line_ptrs[n_lines++] = ptr;
    }
    return n_lines;
}

/*
writes lines to stdout
from 05_pointers_arrays/11_str_sort.c
*/
void write_lines(char *line_ptrs[], int n_lines) {
    while (n_lines-- > 0)
        printf("%s\n", *line_ptrs++);
}

