// print longest line and its length from input

#include <stdio.h>

#define MAX_LINE_PREVIEW 50
#define NULL_CHAR '\0'

int max_len = 0;
char longest_line[MAX_LINE_PREVIEW + 1];

int get_line(char line[]);
void copy(char from[], char to[]);

int main(void) {
    int len = 0;
    char line[MAX_LINE_PREVIEW + 1];

    while ((len = get_line(line)) > 0) {
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
    int ch, col = 0;
    while ((ch = getchar()) != EOF) {
        if (col < MAX_LINE_PREVIEW)
            line[col] = ch;
        ++col;
        if (ch == '\n')
            break;
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
