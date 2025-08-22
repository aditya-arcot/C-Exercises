// fold and left-trim input lines

#include <stdbool.h>
#include <stdio.h>

#define LINE_LENGTH 50
#define NULL_CHAR '\0'

static bool line_overflow = false;
static char buffer[LINE_LENGTH + 1];
static int buffer_idx = 0;
static int buffer_last_whitespace_idx = -1;

void handle_char(char ch);
void handle_newline(void);
void handle_whitespace(char ch);
void flush_and_reset_buffer(void);
void print_buffer(int n);
void shift_buffer_after_last_whitespace(void);
void move_to_next_line(void);
int is_whitespace(char ch);

int main(void) {
    buffer[LINE_LENGTH] = NULL_CHAR;

    for (int ch; (ch = getchar()) != EOF;) {
        handle_char((char)ch);
    }

    // handle end of input without newline
    if (buffer_idx > 0) {
        flush_and_reset_buffer();
    }
}

void handle_char(char ch) {
    if (ch == '\n') {
        handle_newline();
        return;
    }

    if (is_whitespace(ch)) {
        handle_whitespace(ch);
        return;
    }

    if (line_overflow) {
        // cannot break word
        putchar(ch);
        return;
    }

    // full buffer
    if (buffer_idx == LINE_LENGTH) {
        // whitespace in buffer
        if (buffer_last_whitespace_idx != -1) {
            // print buffer till last whitespace, continue to new line
            print_buffer(buffer_last_whitespace_idx);
            move_to_next_line();

            // shift buffer to preserve remaining chars
            shift_buffer_after_last_whitespace();
            buffer[buffer_idx++] = ch;
            buffer_last_whitespace_idx = -1;
            return;
        }

        // no whitespace in buffer
        // flush buffer, print char
        line_overflow = true;
        flush_and_reset_buffer();
        putchar(ch);
        return;
    }

    // partial/empty buffer
    // add char to buffer
    buffer[buffer_idx] = ch;
    ++buffer_idx;
}

void handle_newline(void) {
    flush_and_reset_buffer();
    move_to_next_line();
}

void handle_whitespace(char ch) {
    if (line_overflow) {
        move_to_next_line();
        return;
    }

    // nothing printed, empty buffer
    if (buffer_idx == 0) {
        // ignore for left trim
        return;
    }

    // full buffer
    if (buffer_idx == LINE_LENGTH) {
        flush_and_reset_buffer();
        move_to_next_line();
        return;
    }

    // partial buffer
    // add whitespace to buffer
    buffer[buffer_idx] = ch;
    buffer_last_whitespace_idx = buffer_idx;
    ++buffer_idx;
}

void flush_and_reset_buffer(void) {
    print_buffer(buffer_idx);
    buffer_idx = 0;
    buffer_last_whitespace_idx = -1;
}

void print_buffer(int n) {
    for (int i = 0; i < n; ++i)
        putchar(buffer[i]);
}

void shift_buffer_after_last_whitespace(void) {
    int remaining = buffer_idx - (buffer_last_whitespace_idx + 1);
    for (int i = 0; i < remaining; ++i) {
        buffer[i] = buffer[buffer_last_whitespace_idx + 1 + i];
    }
    buffer_idx = remaining;
}

void move_to_next_line(void) {
    putchar('\n');
    line_overflow = false;
}

int is_whitespace(char ch) {
    return ch == ' ' || ch == '\t';
}
