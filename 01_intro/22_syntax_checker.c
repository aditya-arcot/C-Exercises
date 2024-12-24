/*
    check a C program for syntax errors

    done
        unrecognized preprocessor directive
        mismatched or missing bracket
        unclosed multi-line comment

    to do
        unclosed single or double quote
         - must be on same line unless escaped
        invalid character constant
         - empty, multi-char
        invalid escape sequence
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERROR 1
#define SUCCESS 0
#define NULL_CHAR '\0'
#define MAX_DIRECTIVE_NAME_LENGTH 7
#define MAX_BRACKETS_STACK_LENGTH 1000

const char *valid_directives[] = {"define", "include", "if", "ifdef", "ifndef", "else", "elif", "endif", "undef", "pragma"};

int line = 1;
int col = 1;

int non_blank_line = FALSE;

int directive_line = FALSE;
int directive_name_done = FALSE;
int directive_name_idx = 0;
char directive_buffer[MAX_DIRECTIVE_NAME_LENGTH + 1];

int brackets_stack_idx = 0;
char brackets_stack[MAX_BRACKETS_STACK_LENGTH + 1];

int in_single_comment = FALSE;
int in_multi_comment = FALSE;

void print_syntax_err();
int check_syntax();
int handle_char(char ch);
int perform_newline_checks();
void move_to_new_line();
int push_directive_name_char(char ch);
void print_directive_name();
void print_invalid_directive_name_err();
int is_valid_directive();
int is_matching_strings(const char *a, const char *b);
int push_bracket(char ch);
char pop_bracket();
char get_opening_bracket(char closing_bracket);
void print_brackets_stack();
void print_unclosed_brackets_err();

int main()
{
    directive_buffer[MAX_DIRECTIVE_NAME_LENGTH] = NULL_CHAR;
    brackets_stack[MAX_BRACKETS_STACK_LENGTH] = NULL_CHAR;

    if (check_syntax())
    {
        print_syntax_err();
        return ERROR;
    }
    printf("Checked %d lines. No syntax errors\n", line);
}

void print_syntax_err()
{
    printf("Syntax error - line %d, col %d\n", line, col);
}

int check_syntax()
{
    int ch;
    while ((ch = getchar()) != EOF)
    {
        ++col;
        if (handle_char(ch))
            return ERROR;
    }

    if (perform_newline_checks())
        return ERROR;

    if (brackets_stack_idx > 0)
    {
        print_unclosed_brackets_err();
        return ERROR;
    }

    if (in_multi_comment)
    {
        printf("Unclosed multi-line comment\n");
        return ERROR;
    }

    return SUCCESS;
}

int handle_char(char ch)
{
    if (in_single_comment)
    {
        if (ch == '\n')
        {
            in_single_comment = FALSE;
            move_to_new_line();
        }
        return SUCCESS;
    }

    if (in_multi_comment)
    {
        if (ch == '*')
        {
            ch = getchar();
            if (ch == EOF)
            {
                printf("Unclosed multi-line comment\n");
                return ERROR;
            }

            ++col;

            if (ch == '\n')
            {
                move_to_new_line();
                return SUCCESS;
            }
            if (ch == '/')
            {
                in_multi_comment = FALSE;
                return SUCCESS;
            }
        }
        else if (ch == '\n')
            move_to_new_line();

        return SUCCESS;
    }

    if (ch == '\n')
    {
        if (perform_newline_checks())
        {
            return ERROR;
        }
        move_to_new_line();
        return SUCCESS;
    }
    else if (ch == ' ' || ch == '\t')
    {
        if (directive_line && !directive_name_done && directive_name_idx > 0)
        {
            directive_name_done = TRUE;
            if (!is_valid_directive())
            {
                print_invalid_directive_name_err();
                return ERROR;
            }
        }
        return SUCCESS;
    }
    else if (ch == '#')
    {
        if (non_blank_line)
        {
            printf("Invalid directive\n");
            return ERROR;
        }
        non_blank_line = TRUE;
        directive_line = TRUE;
        return SUCCESS;
    }
    else if (ch == '(' || ch == '{' || ch == '[')
    {
        if (push_bracket(ch))
        {
            return ERROR;
        }
        non_blank_line = TRUE;
        return SUCCESS;
    }
    else if (ch == ')' || ch == '}' || ch == ']')
    {
        char expected_bracket = get_opening_bracket(ch);
        if (expected_bracket == ERROR)
            return ERROR;

        char opening_bracket = pop_bracket();
        if (opening_bracket == ERROR)
            return ERROR;

        if (opening_bracket != expected_bracket)
        {
            printf("Mismatched brackets - %c, %c\n", opening_bracket, ch);
            return ERROR;
        }

        non_blank_line = TRUE;
        return SUCCESS;
    }
    else if (ch == '/')
    {
        ch = getchar();
        if (ch == EOF)
        {
            printf("Unexpected EOF\n");
            return ERROR;
        }
        if (ch == '\n')
        {
            printf("Unexpected newline\n");
            return ERROR;
        }

        ++col;

        if (ch == '/')
        {
            in_single_comment = TRUE;
            return SUCCESS;
        }
        if (ch == '*')
        {
            in_multi_comment = TRUE;
            return SUCCESS;
        }

        non_blank_line = TRUE;
        return SUCCESS;
    }

    non_blank_line = TRUE;

    if (directive_line && !directive_name_done && push_directive_name_char(ch))
    {
        print_invalid_directive_name_err();
        return ERROR;
    }

    return SUCCESS;
}

int perform_newline_checks()
{
    if (directive_line && !directive_name_done && !is_valid_directive())
    {
        print_invalid_directive_name_err();
        return ERROR;
    }
    return SUCCESS;
}

void move_to_new_line()
{
    ++line;
    col = 1;
    non_blank_line = FALSE;
    directive_line = FALSE;
    directive_name_done = FALSE;
    directive_name_idx = 0;
}

int push_directive_name_char(char ch)
{
    if (directive_name_idx == MAX_DIRECTIVE_NAME_LENGTH)
    {
        return ERROR;
    }
    directive_buffer[directive_name_idx++] = ch;
    return SUCCESS;
}

void print_directive_name()
{
    for (int i = 0; i < directive_name_idx; ++i)
        printf("%c", directive_buffer[i]);
}

void print_invalid_directive_name_err()
{
    printf("Invalid directive name - ");
    print_directive_name();
    printf("\n");
}

int is_valid_directive()
{
    directive_buffer[directive_name_idx] = NULL_CHAR;
    size_t num_directives = sizeof(valid_directives) / sizeof(valid_directives[0]);
    for (size_t i = 0; i < num_directives; i++)
    {
        if (is_matching_strings(directive_buffer, valid_directives[i]))
        {
            return TRUE;
        }
    }
    return FALSE;
}

int is_matching_strings(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (*a != *b)
        {
            return FALSE;
        }
        ++a;
        ++b;
    }
    return *a == NULL_CHAR && *b == NULL_CHAR;
}

int push_bracket(char ch)
{
    if (brackets_stack_idx == MAX_BRACKETS_STACK_LENGTH)
    {
        printf("Reached maximum brackets stack depth\n");
        return ERROR;
    }
    brackets_stack[brackets_stack_idx++] = ch;
    return SUCCESS;
}

char pop_bracket()
{
    if (brackets_stack_idx == 0)
    {
        printf("No opening brackets in the stack\n");
        return ERROR;
    }
    return brackets_stack[--brackets_stack_idx];
}

char get_opening_bracket(char closing_bracket)
{
    if (closing_bracket == '}')
        return '{';
    if (closing_bracket == ')')
        return '(';
    if (closing_bracket == ']')
        return '[';
    printf("Invalid closing bracket - %c\n", closing_bracket);
    return ERROR;
}

void print_brackets_stack()
{
    for (int i = 0; i < brackets_stack_idx; ++i)
    {
        printf("%c", brackets_stack[i]);
        if (i != brackets_stack_idx - 1)
            printf(", ");
    }
}

void print_unclosed_brackets_err()
{
    printf("Unclosed brackets - ");
    print_brackets_stack();
    printf("\n");
}