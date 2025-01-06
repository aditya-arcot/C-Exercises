// Stack implementation for calculator

#include <stdio.h>
#include <stdbool.h>
#include "calc.h"

static int stack_pointer;
static double nums_stack[MAX_STACK_DEPTH + 1];

void init_stack(void)
{
    stack_pointer = 0;
    nums_stack[0] = NULL_CHAR;
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
