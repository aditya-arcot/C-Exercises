/*
    RPN Calculator
        spaces between arguments not required, but recommended for clarity
        numbers
            optional negative sign
            optional decimal portion
            max 15 characters (incl negative sign and decimal point)
        operations
            + - * ÷ %
        commands (starting with !)
            h / help
            c / clear
            pr / print
            pop
            peek
            d / dup
            s / swap

    todo
        math functions - sin, exp, pow
        variables
        last printed variable
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#define NULL_CHAR '\0'
#define NEWLINE_CHAR '\n'
#define MAX_LINE_LENGTH 1000
#define MAX_NUM_LENGTH 15
#define MAX_COMMAND_LENGTH 5
#define MAX_STACK_DEPTH 1000
#define ERROR 1

static bool debug = false;
static int stack_pointer = 0;
static double nums_stack[MAX_STACK_DEPTH + 1];

int get_line(char line[], int max);
void handle_line(char line[], int len);
bool is_number(char line[], int idx);
int handle_number(char line[], int idx);
int read_number(char line[], int idx, char num[]);
void handle_operator(char op);
int handle_command(char line[], int idx);
void print_use_help_msg(void);
void print_help_msg(void);

double dbl_abs(double num);
double dbl_mod(double x, double y);
bool str_cmp(const char *s1, const char *s2);

void push(double num);
double pop(void);
double peek(void);
void clear_stack(void);
void print_stack(void);

int main(void)
{
    int len;
    char line[MAX_LINE_LENGTH + 1];
    nums_stack[0] = NULL_CHAR;

    print_help_msg();
    printf("\n\n");

    while ((len = get_line(line, MAX_LINE_LENGTH)) != EOF)
    {
        handle_line(line, len);
    }
    printf("Exiting...\n");
}

// populate char array with line from standard input
// return line length
int get_line(char line[], int max_len)
{
    int ch, i;
    bool blank = true;
    ch = i = 0;

    while (max_len-- > 0 && (ch = getchar()) != EOF && ch != NEWLINE_CHAR)
        // exclude leading blanks
        if (!isblank(ch) || !blank)
        {
            blank = false;
            line[i++] = (char)ch;
        }

    if (i == 0 && ch == EOF)
        return EOF;

    line[i] = NULL_CHAR;

    // skip remaining line
    if (max_len < 0)
    {
        while ((ch = getchar()) != EOF && ch != NEWLINE_CHAR)
            ;
        printf("Warning: input line was trunctated to %s\n", line);
    }

    return i;
}

void handle_line(char line[], int len)
{
    int idx, ch;

    if (len == 0)
        return;

    printf("Input");
    if (debug)
        printf(" (len %d)", len);
    printf(": %s\n", line);

    idx = 0;
    do
    {
        ch = line[idx];
        if (isblank(ch))
            continue;

        if (is_number(line, idx))
            idx = handle_number(line, idx);
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
            handle_operator((char)ch);
        else if (ch == '!')
            idx = handle_command(line, idx + 1); // skip !
        else
        {
            printf("Warning: skipping unknown argument: %c\n", ch);
            print_use_help_msg();
        }
    } while (++idx < len);

    printf("\n\n");
}

bool is_number(char line[], int idx)
{
    int ch = line[idx];

    if (ch == '-')
        ch = line[++idx];

    return isdigit(ch) || ch == '.';
}

// convert number from char array to double and push to stack
int handle_number(char line[], int idx)
{
    double num;
    char num_arr[MAX_NUM_LENGTH + 1];

    idx = read_number(line, idx, num_arr);
    num = atof(num_arr);

    if (debug)
        printf("Number: %s => %g\n", num_arr, num);

    push(num);
    return idx;
}

// populate char array with number from line char array
// return last number character idx
int read_number(char line[], int idx, char num[])
{
    bool leading_zero = true, truncated = false;
    int ch, num_idx = 0;

    if ((ch = line[idx]) == '-')
    {
        idx++;
        num[num_idx++] = '-';
    }

    // integer part
    while (isdigit(ch = line[idx]))
    {
        idx++;

        // ignore leading 0s
        if (ch == '0' && leading_zero)
        {
            continue;
        }
        leading_zero = false;

        // add until max length
        if (num_idx < MAX_NUM_LENGTH)
            num[num_idx++] = (char)ch;
        else
            truncated = true;
    }

    // decimal part
    if (ch == '.')
    {
        idx++;
        if (num_idx < MAX_NUM_LENGTH)
            num[num_idx++] = '.';
        else
            truncated = true;

        while (isdigit(ch = line[idx]))
        {
            idx++;
            if (num_idx < MAX_NUM_LENGTH)
                num[num_idx++] = (char)ch;
            else
                truncated = true;
        }
    }

    num[num_idx] = NULL_CHAR;

    if (truncated)
        printf("Warning: input number was truncated to %s\n", num);

    return idx - 1; // last number idx
}

void handle_operator(char op)
{
    double temp;

    if (debug)
        printf("Operator: %c\n", op);

    switch (op)
    {
    case '+':
        push(pop() + pop());
        break;
    case '-':
        temp = pop();
        push(pop() - temp);
        break;
    case '*':
        push(pop() * pop());
        break;
    case '/':
        temp = pop();
        if (dbl_abs(temp) < DBL_EPSILON)
        {
            printf("Error: cannot divide by 0\n");
            exit(ERROR);
        }
        push(pop() / temp);
        break;
    case '%':
        temp = pop();
        if (dbl_abs(temp) < DBL_EPSILON)
        {
            printf("Error: cannot divide by 0\n");
            exit(ERROR);
        }
        push(dbl_mod(pop(), temp));
        break;
    }
}

// return last command character idx
int handle_command(char line[], int idx)
{
    int ch, i = 0;
    bool overflow = false;
    char command[MAX_COMMAND_LENGTH + 1];
    double temp1, temp2;

    while (isalpha(ch = line[idx]))
    {
        idx++;
        if (i < MAX_COMMAND_LENGTH)
        {
            command[i++] = (char)tolower(ch);
        }
        else
            overflow = true;
    }
    command[i] = NULL_CHAR;

    if (overflow)
    {
        printf("Warning: skipping unknown input command: !%s...\n", command);
        print_use_help_msg();
        return idx - 1;
    }

    if (str_cmp(command, "h") || str_cmp(command, "help"))
        print_help_msg();
    else if (str_cmp(command, "c") || str_cmp(command, "clear"))
        clear_stack();
    else if (str_cmp(command, "pr") || str_cmp(command, "print"))
        print_stack();
    else if (str_cmp(command, "pop"))
        printf("Removed value: %g\n", pop());
    else if (str_cmp(command, "peek"))
        printf("Top value: %g\n", peek());
    else if (str_cmp(command, "d") || str_cmp(command, "dup"))
        push(peek());
    else if (str_cmp(command, "s") || str_cmp(command, "swap"))
    {
        temp1 = pop();
        temp2 = pop();
        push(temp1);
        push(temp2);
    }
    else
    {
        printf("Warning: skipping unknown input command: !%s\n", command);
        print_use_help_msg();
    }

    return idx - 1;
}

void print_use_help_msg(void)
{
    printf("Use !h or !help for documentation\n");
}

void print_help_msg(void)
{
    printf(
        "RPN Calculator\n"
        "    spaces between arguments not required, but recommended for clarity\n"
        "    numbers\n"
        "        optional negative sign\n"
        "        optional decimal portion\n"
        "        max 15 characters (incl negative sign and decimal point)\n"
        "    operations\n"
        "        + - * ÷ %%\n"
        "    commands (starting with !)\n"
        "        h / help\n"
        "        c / clear\n"
        "        pr / print\n"
        "        pop\n"
        "        peek\n"
        "        d / dup\n"
        "        s / swap\n");
}

double dbl_abs(double num)
{
    if (num < 0)
        return -num;
    return num;
}

double dbl_mod(double x, double y)
{
    return x - ((int)(x / y) * y);
}

bool str_cmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return false;
        ++s1;
        ++s2;
    }
    return *s1 == NULL_CHAR && *s2 == NULL_CHAR;
}

void push(double num)
{
    if (debug)
        printf("Pushing %g to stack...\n", num);
    if (stack_pointer == MAX_STACK_DEPTH)
    {
        printf("Error: stack overflow\n");
        exit(ERROR);
    }
    nums_stack[stack_pointer++] = num;
    if (debug)
    {
        printf("Pushed %g to stack\n", num);
        print_stack();
    }
}

double pop(void)
{
    double num;
    if (debug)
        printf("Popping from stack...\n");
    if (stack_pointer == 0)
    {
        printf("Error: stack underflow\n");
        exit(ERROR);
    }
    num = nums_stack[--stack_pointer];
    if (debug)
    {
        printf("Popped %g from stack\n", num);
        print_stack();
    }
    return num;
}

double peek(void)
{
    double num;
    if (debug)
        printf("Peeking from stack...\n");
    if (stack_pointer == 0)
    {
        printf("Error: stack underflow\n");
        exit(ERROR);
    }
    num = nums_stack[stack_pointer - 1];
    if (debug)
    {
        printf("Peeked %g from stack\n", num);
        print_stack();
    }
    return num;
}

void clear_stack(void)
{
    if (debug)
        printf("Clearing stack...\n");
    stack_pointer = 0;
    nums_stack[0] = NULL_CHAR;
    if (debug)
        print_stack();
}

void print_stack(void)
{
    int i;
    printf("Stack: ");
    for (i = 0; i < stack_pointer; i++)
    {
        printf("%g", nums_stack[i]);
        if (i != stack_pointer - 1)
            printf(", ");
    }
    printf("\n");
}
