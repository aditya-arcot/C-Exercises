// Global symbolic constants, variables, and function prototypes

#include <stdbool.h>

#define NULL_CHAR '\0'
#define NEWLINE_CHAR '\n'
#define MAX_LINE_LENGTH 1000
#define MAX_NUM_LENGTH 15
#define MAX_CONSTANT_LENGTH 2
// #define MAX_VARIABLE_LENGTH 10
#define MAX_COMMAND_LENGTH 5
#define MAX_FUNCTION_LENGTH 5
#define MAX_STACK_DEPTH 1000

extern bool debug;

double dbl_abs(double num);
double dbl_mod(double x, double y);
bool str_eq(const char *s1, const char *s2);

void init_stack(void);
void push(double num);
double pop(void);
double peek(void);
void clear_stack(void);
void print_stack(void);
