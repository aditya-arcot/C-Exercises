// reverse and print each line of input

#include "line_utils.h"
#include <stdio.h>

#define MAX_LINE 100

void reverse(char line[], int len);

int main(void) {
    char line[MAX_LINE + 1];
    for (int len = 0; (len = get_line(line, MAX_LINE, false, false)) > 0;)
        reverse(line, len);
}

void reverse(char line[], int len) {
    for (int i = len - 1; i >= 0; --i)
        putchar(line[i]);
    putchar('\n');
}
