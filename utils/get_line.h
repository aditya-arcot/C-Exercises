#ifndef GET_LINE_H
#define GET_LINE_H

#include <stdbool.h>

int get_line(char line[], int max_len, bool allow_overflow, bool exclude_leading_blanks);

#endif
