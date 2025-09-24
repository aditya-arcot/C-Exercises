/*
    simple tail program

    usage: tail [n]
        n is number of lines from end
*/

#include "alloc.h"
#include "line_utils.h"
#include "str_utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 100

static char *line_ptrs[MAX_LINES];

int main(int argc, char *argv[]) {
    int tail_lines, num_lines, start_line;

    tail_lines = 0;
    while (--argc > 0)
        tail_lines = atoi(*++argv);
    if (tail_lines < 0)
        tail_lines = -1 * tail_lines;
    else if (tail_lines == 0)
        tail_lines = 10;

    num_lines = read_lines(line_ptrs, MAX_LINES);
    if (num_lines == ALLOC_ERR) {
        printf("Error: alloc failed\n");
        return 1;
    }
    if (num_lines == LINES_OVERFLOW)
        num_lines = MAX_LINES;

    start_line = (num_lines - tail_lines) > 0 ? (num_lines - tail_lines) : 0;
    write_lines(&line_ptrs[start_line], num_lines - start_line);
}
