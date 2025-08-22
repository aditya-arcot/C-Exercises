// print longest line and its length from input

#include <stdio.h>

#define MAX_LINE_PREVIEW 50
#define NULL_CHAR '\0'

static int max_len = 0;
static char longest_line[MAX_LINE_PREVIEW + 1];

int get_line(char line[]);
void copy(char from[], char to[]);

int main(void) {
    char line[MAX_LINE_PREVIEW + 1];

    for (int len = 0; (len = get_line(line)) > 0;) {
        // latest line for tie
        if (len >= max_len) {
            max_len = len;
            copy(line, longest_line);
        }
    }

    if (max_len > 0) {
        if (max_len > MAX_LINE_PREVIEW)
            printf("Longest line (%d): %s...\n", max_len, longest_line);
        else
            printf("Longest line (%d): %s\n", max_len, longest_line);
    } else
        printf("No input\n");
}

// read line into array, return length
int get_line(char line[]) {
    int col = 0;
    for (int ch; (ch = getchar()) != EOF && ch != '\n';) {
        if (col < MAX_LINE_PREVIEW)
            line[col] = (char)ch;
        ++col;
    }

    // null-terminate string
    if (col < MAX_LINE_PREVIEW)
        line[col] = NULL_CHAR;
    else
        line[MAX_LINE_PREVIEW] = NULL_CHAR;

    return col;
}

// copy character array
void copy(char from[], char to[]) {
    // stop at null terminator
    for (int i = 0; (to[i] = from[i]) != NULL_CHAR; ++i)
        ;
}
