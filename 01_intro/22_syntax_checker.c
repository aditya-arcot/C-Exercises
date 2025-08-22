/*
    Check a C program for syntax errors

    Purpose:
        A lightweight syntax checker for C programs that identifies basic errors and provides detailed feedback.

    Errors Detected:
        - Unrecognized preprocessor directives
        - Unclosed or mismatched brackets ({}, (), [])
        - Unclosed multi-line comments
        - Unclosed string literals ("...")
        - Unclosed or invalid character literals ('...')
        - Invalid escape sequences in strings or character literals

    Valid Directives:
        #define, #include, #if, #ifdef, #ifndef, #else, #elif, #endif, #undef, #pragma

    Notable Features:
        - Provides detailed error information, including line and column numbers
        - Ensures correct nesting of brackets
        - Handles continuation lines (ending with a backslash)
        - Recognizes single-line and multi-line comments

    Limitations:
        - Does not handle semantic errors or advanced syntax constructs
        - Designed for simple C code syntax validation, not for full parsing or compilation
*/

#include <stdbool.h>
#include <stdio.h>

#define ERROR 1
#define SUCCESS 0
#define NULL_CHAR '\0'
#define MAX_DIRECTIVE_NAME_LENGTH 7
#define MAX_BRACKETS_STACK_LENGTH 1000
#define MAX_CHAR_LENGTH 2

static bool debug = false;
static int line = 1;
static int col = 1;
static bool non_blank_line = false;
static bool directive_line = false;
static bool directive_name_done = false;
static int directive_name_idx = 0;
static char directive_buffer[MAX_DIRECTIVE_NAME_LENGTH + 1];
static const char *valid_directives[] = {"define", "include", "if",    "ifdef", "ifndef",
                                         "else",   "elif",    "endif", "undef", "pragma"};
static int brackets_stack_idx = 0;
static char brackets_stack[MAX_BRACKETS_STACK_LENGTH + 1];
static bool in_single_comment = false;
static bool in_multi_comment = false;
static bool in_string = false;
static bool in_char = false;
static int char_buffer_idx = 0;
static char char_buffer[MAX_CHAR_LENGTH + 1];
static bool escaped = false;
static const char valid_escapes[] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '\'', '"', '?', '0'};

int are_matching_strings(const char *a, const char *b);
void print_syntax_err(void);
int check_syntax(void);
int handle_char(int ch);
int perform_newline_checks(void);
void move_to_new_line(void);
int push_directive_name_char(char ch);
void print_directive_name(void);
void print_invalid_directive_name_err(void);
int is_valid_directive(void);
int push_bracket(char ch);
char pop_bracket(void);
char get_opening_bracket(char closing_bracket);
void print_brackets_stack(void);
void print_unclosed_brackets_err(void);
int push_char(char ch);
int pop_char(void);
int is_valid_escape(char escape);

int main(void) {
    directive_buffer[MAX_DIRECTIVE_NAME_LENGTH] = NULL_CHAR;
    brackets_stack[MAX_BRACKETS_STACK_LENGTH] = NULL_CHAR;
    char_buffer[MAX_CHAR_LENGTH] = NULL_CHAR;

    if (check_syntax()) {
        print_syntax_err();
        return ERROR;
    }
    printf("Checked %d lines. No syntax errors\n", line);
}

int are_matching_strings(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b)
            return false;
        ++a;
        ++b;
    }
    return *a == NULL_CHAR && *b == NULL_CHAR;
}

void print_syntax_err(void) {
    printf("Syntax error - line %d, col %d\n", line, col);
}

int check_syntax(void) {
    for (int ch; (ch = getchar()) != EOF;) {
        ++col;
        if (handle_char(ch))
            return ERROR;
    }

    if (perform_newline_checks())
        return ERROR;

    if (brackets_stack_idx > 0) {
        print_unclosed_brackets_err();
        return ERROR;
    }

    if (in_multi_comment) {
        printf("Unclosed multi-line comment\n");
        return ERROR;
    }

    if (in_string) {
        printf("Unclosed string\n");
        return ERROR;
    }

    if (in_char) {
        printf("Unclosed character literal\n");
        return ERROR;
    }

    return SUCCESS;
}

int handle_char(int ch) {
    if (debug) {
        if (ch == '\n') {
            printf("line %-3d col %-3d [newline]\n", line, col);
        } else if (ch == ' ') {
            printf("line %-3d col %-3d [space]\n", line, col);
        } else if (ch == '\t') {
            printf("line %-3d col %-3d [tab]\n", line, col);
        } else {
            printf("line %-3d col %-3d %c\n", line, col, ch);
        }
    }

    if (in_single_comment) {
        if (ch == '\n') {
            in_single_comment = false;
            move_to_new_line();
        }
        return SUCCESS;
    }

    if (in_multi_comment) {
        if (ch == '*') {
            ch = (char)getchar();
            if (ch == EOF) {
                printf("Unclosed multi-line comment\n");
                return ERROR;
            }

            ++col;

            if (ch == '\n') {
                move_to_new_line();
                return SUCCESS;
            }
            if (ch == '/') {
                in_multi_comment = false;
                return SUCCESS;
            }
        } else if (ch == '\n')
            move_to_new_line();

        return SUCCESS;
    }

    if (escaped) {
        if (ch == '\n') {
            escaped = false;
            if (in_char && pop_char())
                return ERROR;
            move_to_new_line();
            return SUCCESS;
        }
        if (in_char && push_char((char)ch))
            return ERROR;
        if (!is_valid_escape((char)ch)) {
            printf("Invalid escape sequence\n");
            return ERROR;
        }
        escaped = false;
        non_blank_line = true;
        return SUCCESS;
    }

    if (ch == '\\') {
        if (in_char && push_char((char)ch))
            return ERROR;
        escaped = true;
        non_blank_line = true;
        return SUCCESS;
    }

    if (in_string) {
        if (ch == '"') {
            in_string = false;
            return SUCCESS;
        }
        if (ch == '\n') {
            printf("Unclosed string\n");
            return ERROR;
        }
        return SUCCESS;
    }

    if (in_char) {
        if (ch == '\'') {
            in_char = false;
            if (char_buffer_idx == 1) {
                char_buffer_idx = 0;
                return SUCCESS;
            }
            if (char_buffer_idx < 1) {
                printf("Empty character literal\n");
                return ERROR;
            }
            if (char_buffer[0] != '\\') {
                printf("character literal too long\n");
                return ERROR;
            }
            // must be escape sequence - already tested
            char_buffer_idx = 0;
            return SUCCESS;
        }
        if (ch == '\n') {
            printf("Unclosed character literal\n");
            return ERROR;
        }
        return push_char((char)ch);
    }

    if (ch == '\n') {
        if (perform_newline_checks()) {
            return ERROR;
        }
        move_to_new_line();
        return SUCCESS;
    } else if (ch == ' ' || ch == '\t') {
        if (directive_line && !directive_name_done && directive_name_idx > 0) {
            directive_name_done = true;
            if (!is_valid_directive()) {
                print_invalid_directive_name_err();
                return ERROR;
            }
        }
        return SUCCESS;
    } else if (ch == '#') {
        if (non_blank_line) {
            printf("Invalid directive\n");
            return ERROR;
        }
        non_blank_line = true;
        directive_line = true;
        return SUCCESS;
    } else if (ch == '(' || ch == '{' || ch == '[') {
        if (push_bracket((char)ch)) {
            return ERROR;
        }
        non_blank_line = true;
        return SUCCESS;
    } else if (ch == ')' || ch == '}' || ch == ']') {
        char expected_bracket = get_opening_bracket((char)ch);
        if (expected_bracket == ERROR)
            return ERROR;

        char opening_bracket = pop_bracket();
        if (opening_bracket == ERROR)
            return ERROR;

        if (opening_bracket != expected_bracket) {
            printf("Mismatched brackets - %c, %c\n", opening_bracket, ch);
            return ERROR;
        }

        non_blank_line = true;
        return SUCCESS;
    } else if (ch == '/') {
        ch = (char)getchar();
        if (ch == EOF) {
            printf("Unexpected EOF\n");
            return ERROR;
        }
        if (ch == '\n') {
            printf("Unexpected newline\n");
            return ERROR;
        }

        ++col;

        if (ch == '/') {
            in_single_comment = true;
            return SUCCESS;
        }
        if (ch == '*') {
            in_multi_comment = true;
            return SUCCESS;
        }

        non_blank_line = true;
        return SUCCESS;
    } else if (ch == '"') {
        non_blank_line = true;
        in_string = true;
        return SUCCESS;
    } else if (ch == '\'') {
        non_blank_line = true;
        in_char = true;
        return SUCCESS;
    }

    non_blank_line = true;

    if (directive_line && !directive_name_done && push_directive_name_char((char)ch)) {
        print_invalid_directive_name_err();
        return ERROR;
    }

    return SUCCESS;
}

int perform_newline_checks(void) {
    if (directive_line && !directive_name_done && !is_valid_directive()) {
        print_invalid_directive_name_err();
        return ERROR;
    }
    return SUCCESS;
}

void move_to_new_line(void) {
    ++line;
    col = 1;
    non_blank_line = false;
    directive_line = false;
    directive_name_done = false;
    directive_name_idx = 0;
}

int push_directive_name_char(char ch) {
    if (directive_name_idx == MAX_DIRECTIVE_NAME_LENGTH) {
        return ERROR;
    }
    directive_buffer[directive_name_idx++] = ch;
    return SUCCESS;
}

void print_directive_name(void) {
    for (int i = 0; i < directive_name_idx; ++i)
        printf("%c", directive_buffer[i]);
}

void print_invalid_directive_name_err(void) {
    printf("Invalid directive name - ");
    print_directive_name();
    printf("\n");
}

int is_valid_directive(void) {
    directive_buffer[directive_name_idx] = NULL_CHAR;
    size_t num_directives = sizeof(valid_directives) / sizeof(valid_directives[0]);
    for (size_t i = 0; i < num_directives; ++i) {
        if (are_matching_strings(directive_buffer, valid_directives[i])) {
            return true;
        }
    }
    return false;
}

int push_bracket(char ch) {
    if (brackets_stack_idx == MAX_BRACKETS_STACK_LENGTH) {
        printf("Reached maximum brackets stack depth\n");
        return ERROR;
    }
    brackets_stack[brackets_stack_idx++] = ch;
    return SUCCESS;
}

char pop_bracket(void) {
    if (brackets_stack_idx == 0) {
        printf("No opening brackets in the stack\n");
        return ERROR;
    }
    return brackets_stack[--brackets_stack_idx];
}

char get_opening_bracket(char closing_bracket) {
    if (closing_bracket == '}')
        return '{';
    if (closing_bracket == ')')
        return '(';
    if (closing_bracket == ']')
        return '[';
    printf("Invalid closing bracket - %c\n", closing_bracket);
    return ERROR;
}

void print_brackets_stack(void) {
    for (int i = 0; i < brackets_stack_idx; ++i) {
        printf("%c", brackets_stack[i]);
        if (i != brackets_stack_idx - 1)
            printf(", ");
    }
}

void print_unclosed_brackets_err(void) {
    printf("Unclosed brackets - ");
    print_brackets_stack();
    printf("\n");
}

int push_char(char ch) {
    if (char_buffer_idx == MAX_CHAR_LENGTH) {
        printf("character literal too long\n");
        return ERROR;
    }
    char_buffer[char_buffer_idx++] = ch;
    return SUCCESS;
}

int pop_char(void) {
    if (char_buffer_idx == 0) {
        printf("No char in the buffer\n");
        return ERROR;
    }
    --char_buffer_idx;
    return SUCCESS;
}

int is_valid_escape(char escape) {
    size_t num_escapes = sizeof(valid_escapes) / sizeof(valid_escapes[0]);
    for (size_t i = 0; i < num_escapes; ++i) {
        if (escape == valid_escapes[i]) {
            return true;
        }
    }
    return false;
}
