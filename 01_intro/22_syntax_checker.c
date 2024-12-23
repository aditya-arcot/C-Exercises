/*
    check a C program for syntax errors

    done
        unrecognized preprocessor directive
        mismatched or missing bracket

    to do
        unclosed single or double quote
         - must be on same line unless escaped
        invalid character constant
         - empty, multi-char
        invalid escape sequence
        unclosed multi-line comment
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

int line = 0;
int col = 0;

int non_blank_line = FALSE;

int directive_line = FALSE;
int directive_name_done = FALSE;
int directive_name_idx = 0;
char directive_buffer[MAX_DIRECTIVE_NAME_LENGTH + 1];

int brackets_stack_idx = 0;
char brackets_stack[MAX_BRACKETS_STACK_LENGTH + 1];

int handle_char(char ch);
int perform_newline_checks();
void reset_vars();
int push_directive_name_char(char ch);
void print_directive_name();
int is_valid_directive();
int is_matching_strings(const char *a, const char *b);
int push_bracket(char ch);
char pop_bracket();
char get_opening_bracket(char closing_bracket);
void print_brackets_stack();

int main()
{
    directive_buffer[MAX_DIRECTIVE_NAME_LENGTH] = NULL_CHAR;
    brackets_stack[MAX_BRACKETS_STACK_LENGTH] = NULL_CHAR;

    int ch;
    while ((ch = getchar()) != EOF)
    {
        if (handle_char(ch))
        {
            printf(" - line %d, col %d\n", line, col);
            return ERROR;
        }
    }

    if (perform_newline_checks())
    {
        printf(" - line %d, col %d\n", line, col);
        return ERROR;
    }

    if (brackets_stack_idx > 0)
    {
        printf("Unclosed brackets - ");
        print_brackets_stack();
        printf("\n");
        return ERROR;
    }

    printf("Checked %d lines. No syntax errors\n", line + 1);
}

int handle_char(char ch)
{
    ++col;
    if (ch == '\n')
    {
        if (perform_newline_checks())
        {
            return ERROR;
        }

        ++line;
        col = 0;
        reset_vars();
        return SUCCESS;
    }
    else if (ch == ' ' || ch == '\t')
    {
        if (directive_line && !directive_name_done && directive_name_idx > 0)
        {
            directive_name_done = TRUE;
            if (!is_valid_directive())
            {
                printf("Invalid directive name - ");
                print_directive_name();
                return ERROR;
            }
        }
        return SUCCESS;
    }
    else if (ch == '#')
    {
        if (non_blank_line)
        {
            printf("Directive syntax error");
            return 1;
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
            printf("Mismatched brackets - %c, %c", opening_bracket, ch);
            return ERROR;
        }
        non_blank_line = TRUE;
        return SUCCESS;
    }

    non_blank_line = TRUE;

    if (directive_line && !directive_name_done && push_directive_name_char(ch))
    {
        printf("Invalid directive name - ");
        print_directive_name();
        return ERROR;
    }

    return SUCCESS;
}

int perform_newline_checks()
{
    if (directive_line && !directive_name_done && !is_valid_directive())
    {
        printf("Invalid directive name - ");
        print_directive_name();
        return ERROR;
    }
    return SUCCESS;
}

void reset_vars()
{
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
        printf("Reached maximum brackets stack depth");
        return ERROR;
    }
    brackets_stack[brackets_stack_idx++] = ch;
    return SUCCESS;
}

char pop_bracket()
{
    if (brackets_stack_idx == 0)
    {
        printf("No opening brackets in the stack");
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
        printf("%c", brackets_stack[i]);
}
