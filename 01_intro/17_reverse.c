// reverse and print each line of input

#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE 10
#define NULL_CHAR '\0'

int get_line(char line[]);
void reverse(char line[], int len);

int main(void) {
    int len = 0;
    char line[MAX_LINE + 1];
    while ((len = get_line(line)) > 0)
        reverse(line, len);
}

int get_line(char line[]) {
    int ch, col = 0;
    bool overflow = false;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (col == MAX_LINE) {
            overflow = true;
            break;
        }
        line[col++] = (char)ch;
    }

    if (overflow) {
        while ((ch = getchar()) != EOF && ch != '\n')
            ;
        printf("Truncating input to %d characters\n", MAX_LINE);
    }

    line[col] = NULL_CHAR;
    return col;
}

void reverse(char line[], int len) {
    for (int i = len - 1; i >= 0; --i)
        putchar(line[i]);
    putchar('\n');
}
