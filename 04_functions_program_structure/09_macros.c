#include <stdio.h>

// object-like
#define FOR for
#define INFINITE_FOR FOR(;;)

// function-like
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// stringizing operator
#define DEBUG_PRINT(expr) printf(#expr ": %d\n", expr)

// token pasting operator
#define JOIN_TOKENS(token1, token2) token1##token2

// check defined
#if defined(FOR)
// statements
#elif !defined(MAX)
// statements
#else
// statements
#endif

int main(void) {
    FOR(int i = 0; i < 1; i++) {
        continue;
    }

    INFINITE_FOR {
        break;
    }

    int i = 5;
    int j = 7;
    // side effect duplicated
    printf("%d\n", MAX(++i, ++j));

    DEBUG_PRINT(i);

    int abc = 10;
    printf("%d\n", JOIN_TOKENS(a, bc));

    DEBUG_PRINT(JOIN_TOKENS(a, bc));
}
