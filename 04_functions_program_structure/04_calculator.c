/*
    Reverse Polish Notation Calculator

    See print_help_msg() for usage and supported input.
    TODO - variables (require knowledge of structs)
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define NULL_CHAR '\0'
#define NEWLINE_CHAR '\n'
#define MAX_LINE_LENGTH 1000
#define MAX_NUM_LENGTH 15
#define MAX_CONSTANT_LENGTH 2
// #define MAX_VARIABLE_LENGTH 10
#define MAX_COMMAND_LENGTH 5
#define MAX_FUNCTION_LENGTH 5
#define MAX_STACK_DEPTH 1000

static bool debug = false;
static int stack_pointer = 0;
static double nums_stack[MAX_STACK_DEPTH + 1];

int get_line(char line[], int max);
void handle_line(char line[], int len);
bool is_number(char line[], int idx);
int handle_number(char line[], int idx);
int read_number(char line[], int idx, char num[]);
int handle_constant(char line[], int idx);
// int handle_variable(char line[], int idx);
void handle_operator(char op);
int handle_function(char line[], int idx);
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
        else if (ch == '#')
            idx = handle_constant(line, idx + 1);
        // else if (ch == '$')
        //     idx = handle_variable(line, idx + 1);
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
            handle_operator((char)ch);
        else if (ch == '!')
            idx = handle_command(line, idx + 1);
        else if (ch == '@')
            idx = handle_function(line, idx + 1);
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

// return last constant character idx
int handle_constant(char line[], int idx)
{
    int ch, i = 0;
    bool overflow = false;
    char constant[MAX_CONSTANT_LENGTH + 1];

    while (isalpha(ch = line[idx]))
    {
        idx++;
        if (i < MAX_CONSTANT_LENGTH)
            constant[i++] = (char)tolower(ch);
        else
            overflow = true;
    }
    constant[i] = NULL_CHAR;

    if (overflow)
    {
        printf("Warning: skipping unknown constant: #%s...\n", constant);
        print_use_help_msg();
        return idx - 1;
    }

    if (debug)
        printf("Constant: %s\n", constant);

    if (str_cmp(constant, "e"))
        push(M_E);
    else if (str_cmp(constant, "pi"))
        push(M_PI);
    else
    {
        printf("Warning: skipping unknown constant: #%s\n", constant);
        print_use_help_msg();
    }

    return idx - 1;
}

// int handle_variable(char line[], int idx)
// {
//     int ch, i = 0;
//     bool assignment = false, overflow = false;
//     char variable[MAX_VARIABLE_LENGTH + 1];

//     if ((ch = line[idx]) == '=')
//     {
//         idx++;
//         assignment = true;
//     }

//     while (isalpha(ch = line[idx]))
//     {
//         idx++;
//         if (i < MAX_VARIABLE_LENGTH)
//             variable[i++] = (char)tolower(ch);
//         else
//             overflow = true;
//     }
//     variable[i] = NULL_CHAR;

//     if (overflow)
//         printf("Warning: variable name is too long. Using first %d characters - %s\n", MAX_VARIABLE_LENGTH, variable);

//     if (debug)
//         printf("Variable: %s\n", variable);

//     if (assignment)
//         assign_variable(variable, pop());
//     else
//         if (variable_exists(variable))
//             push(get_variable_value(variable));
//         else
//             printf("Warning: unknown variable: %s. Ignoring usage\n", variable);

//     return idx - 1;
// }

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
        if (dbl_abs(peek()) < DBL_EPSILON)
        {
            printf("Error: cannot divide by 0. Ignoring operation\n");
            return;
        }
        temp = pop();
        push(pop() / temp);
        break;
    case '%':
        if (dbl_abs(peek()) < DBL_EPSILON)
        {
            printf("Error: cannot divide by 0. Ignoring operation\n");
            return;
        }
        temp = pop();
        push(dbl_mod(pop(), temp));
        break;
    }
}

// return last function character idx
int handle_function(char line[], int idx)
{
    int ch, i = 0;
    bool overflow = false;
    char function[MAX_FUNCTION_LENGTH + 1];

    while (isalpha(ch = line[idx]))
    {
        idx++;
        if (i < MAX_FUNCTION_LENGTH)
            function[i++] = (char)tolower(ch);
        else
            overflow = true;
    }
    function[i] = NULL_CHAR;

    if (overflow)
    {
        printf("Warning: skipping unknown function: @%s...\n", function);
        print_use_help_msg();
        return idx - 1;
    }

    if (debug)
        printf("Function: %s\n", function);

    if (str_cmp(function, "floor"))
        push(floor(pop()));
    else if (str_cmp(function, "ceil"))
        push(ceil(pop()));
    else if (str_cmp(function, "round"))
        push(round(pop()));
    else if (str_cmp(function, "trunc"))
        push(trunc(pop()));
    else if (str_cmp(function, "abs"))
        push(dbl_abs(pop()));
    else if (str_cmp(function, "rand"))
        push(rand() / (double)RAND_MAX);
    else if (str_cmp(function, "min"))
        push(fmin(pop(), pop()));
    else if (str_cmp(function, "max"))
        push(fmax(pop(), pop()));
    else if (str_cmp(function, "sqrt"))
    {
        if (peek() < 0)
        {
            printf("Error: cannot take square root of negative number. Ignoring operation\n");
            return idx - 1;
        }
        push(sqrt(pop()));
    }
    else if (str_cmp(function, "pow"))
    {
        double y = pop();
        push(pow(pop(), y));
    }
    else if (str_cmp(function, "exp"))
        push(exp(pop()));
    else if (str_cmp(function, "log"))
        push(log10(pop()));
    else if (str_cmp(function, "ln"))
        push(log(pop()));
    else if (str_cmp(function, "sin"))
        push(sin(pop()));
    else if (str_cmp(function, "cos"))
        push(cos(pop()));
    else if (str_cmp(function, "tan"))
        push(tan(pop()));
    else if (str_cmp(function, "asin"))
        push(asin(pop()));
    else if (str_cmp(function, "acos"))
        push(acos(pop()));
    else if (str_cmp(function, "atan"))
        push(atan(pop()));
    else
    {
        printf("Warning: skipping unknown function: @%s\n", function);
        print_use_help_msg();
    }

    return idx - 1;
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
            command[i++] = (char)tolower(ch);
        else
            overflow = true;
    }
    command[i] = NULL_CHAR;

    if (overflow)
    {
        printf("Warning: skipping unknown command: !%s...\n", command);
        print_use_help_msg();
        return idx - 1;
    }

    if (debug)
        printf("Command: %s\n", command);

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
        printf("Warning: skipping unknown command: !%s\n", command);
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
        "Reverse Polish Notation Calculator\n"
        "\n"
        "Usage:\n"
        "    Enter numbers, constants, operators, functions, or commands to manipulate the stack.\n"
        // "    Enter numbers, constants, variables, operators, functions, or commands to manipulate the stack.\n"
        "    Each line can contain a maximum of 1000 characters.\n"
        "    Spaces between arguments are optional but recommended for clarity.\n"
        "    Trignometric functions use units of radians.\n"
        "\n"
        "Supported Input:\n"
        "    Numbers:\n"
        "        Optional negative sign\n"
        "        Optional decimal portion\n"
        "        Maximum length: 15 characters (including '-' and '.')\n"
        "\n"
        "    Constants (start with '#'):\n"
        "        #e     Euler's Number (2.71828)\n"
        "        #pi    Pi (3.14159)\n"
        // "\n"
        // "    Variables (start with '$'):\n"
        // "        Case insensitive\n"
        // "        Allowed characters: a-z, A-Z\n"
        // "        Maximum length: 10 characters (excluding '$')\n"
        // "        $=var1      Pop the top stack value and assign it to a variable var1.\n"
        // "        $var1       Push the value of variable var1 to the stack.\n"
        "\n"
        "    Operators:\n"
        "        +   Addition\n"
        "        -   Subtraction\n"
        "        *   Multiplication\n"
        "        /   Division\n"
        "        %%   Modulus\n"
        "\n"
        "    Functions (start with '@'):\n"
        "        @floor  Floor\n"
        "        @ceil   Ceiling\n"
        "        @round  Round\n"
        "        @trunc  Truncate\n"
        "        @abs    Absolute Value\n"
        "        @rand   Random Number Between 0 and 1\n"
        "        @min    Minimum of x and y\n"
        "        @max    Maximum of x and y\n"
        "        @sqrt   Square Root\n"
        "        @pow    Power (x^y)\n"
        "        @exp    Exponential (e^x)\n"
        "        @log    Base-10 Logarithm\n"
        "        @ln     Natural Logarithm\n"
        "        @sin    Sine\n"
        "        @cos    Cosine\n"
        "        @tan    Tangent\n"
        "        @asin   Inverse Sine\n"
        "        @acos   Inverse Cosine\n"
        "        @atan   Inverse Tangent\n"
        "\n"
        "    Commands (start with '!'):\n"
        "        !h or !help     Show this help message.\n"
        "        !c or !clear    Clear the stack.\n"
        "        !pr or !print   Display the current stack.\n"
        "        !pop            Remove and display the top stack value.\n"
        "        !peek           Display the top stack value without removing it.\n"
        "        !d or !dup      Duplicate the top stack value.\n"
        "        !s or !swap     Swap the top two stack values.\n"
        "\n"
        "Example:\n"
        "    Input: 3 4 + 5 * !pr\n"
        "    Output: Stack: 35);\n");
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
        printf("Error: stack overflow. Ignoring value\n");
        return;
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
        printf("Error: stack underflow. Returning 0\n");
        return 0;
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
        printf("Error: stack underflow. Returning 0\n");
        return 0;
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
