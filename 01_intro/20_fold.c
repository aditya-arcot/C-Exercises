// fold and left-trim input lines

#include <stdio.h>

#define COLUMN_WIDTH 20
#define NULL_CHAR '\0'

int col = 0;
int buffer_idx = 0;
int last_whitespace = -1;
char buffer[COLUMN_WIDTH + 1];

int is_whitespace(char ch) { return ch == ' ' || ch == '\t'; }
void flush_and_reset_buffer();
void print_buffer(int n);
void shift_buffer_after_last_whitespace();
void move_to_next_line();
void handle_char(char ch);
void handle_newline();
void handle_whitespace(char ch);

int main()
{
    int ch;
    buffer[COLUMN_WIDTH] = NULL_CHAR;

    while ((ch = getchar()) != EOF)
    {
        handle_char(ch);
    }

    // in case end of input without newline
    if (buffer_idx > 0)
    {
        flush_and_reset_buffer();
    }
}

void flush_and_reset_buffer()
{
    print_buffer(buffer_idx);
    buffer_idx = 0;
    last_whitespace = -1;
}

void print_buffer(int n)
{
    for (int i = 0; i < n; ++i)
        putchar(buffer[i]);
}

void shift_buffer_after_last_whitespace()
{
    int remaining = buffer_idx - (last_whitespace + 1);
    for (int i = 0; i < remaining; ++i)
    {
        buffer[i] = buffer[last_whitespace + 1 + i];
    }
    buffer_idx = remaining;
}

void move_to_next_line()
{
    putchar('\n');
    col = 0;
}

void handle_char(char ch)
{
    if (ch == '\n')
        return handle_newline();

    if (is_whitespace(ch))
        return handle_whitespace(ch);

    // buffer previously printed
    if (col > 0)
    {
        // print char
        putchar(ch);
        return;
    }

    // full buffer
    if (buffer_idx == COLUMN_WIDTH)
    {
        // whitespace in buffer
        if (last_whitespace != -1)
        {
            // print buffer till last whitespace, continue to new line
            print_buffer(last_whitespace);
            move_to_next_line();

            // shift buffer to preserve remaining chars
            shift_buffer_after_last_whitespace();
            buffer[buffer_idx++] = ch;
            last_whitespace = -1;
            return;
        }

        // no whitespace in buffer
        // flush buffer, print char
        col += buffer_idx;
        flush_and_reset_buffer();
        putchar(ch);
        ++col;
        return;
    }

    // partial/empty buffer
    // add char to buffer
    buffer[buffer_idx] = ch;
    ++buffer_idx;
}

void handle_newline()
{
    flush_and_reset_buffer();
    move_to_next_line();
}

void handle_whitespace(char ch)
{
    // buffer previously printed
    if (col > 0)
    {
        return move_to_next_line();
    }

    // nothing printed, empty buffer
    if (buffer_idx == 0)
    {
        // ignore for left trim
        return;
    }

    // full buffer
    if (buffer_idx == COLUMN_WIDTH)
    {
        flush_and_reset_buffer();
        return move_to_next_line();
    }

    // partial buffer
    // add whitespace to buffer
    buffer[buffer_idx] = ch;
    last_whitespace = buffer_idx;
    ++buffer_idx;
}