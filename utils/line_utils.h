#ifndef LINE_UTILS_H
#define LINE_UTILS_H

#include <stdbool.h>

#define LINES_OVERFLOW -1
#define ALLOC_ERR -2

int get_line(char line[], int max_len, bool allow_overflow, bool exclude_leading_blanks);
int read_lines(char *line_ptrs[], int max_lines);
void write_lines(char *line_ptrs[], int n_lines);

#endif
