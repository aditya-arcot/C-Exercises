#include <stdio.h>

#define SWAP(type, x, y) \
    {                    \
        type temp;       \
        temp = x;        \
        x = y;           \
        y = temp;        \
    }
#define DEBUG_PRINT(expr) printf(#expr ": %d\n", expr)

int main(void)
{
    int a = 5;
    int b = 10;

    DEBUG_PRINT(a);
    DEBUG_PRINT(b);

    SWAP(int, a, b);

    DEBUG_PRINT(a);
    DEBUG_PRINT(b);
}
