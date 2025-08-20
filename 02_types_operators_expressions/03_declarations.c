#include <stdio.h>

static const double e; // initialized to 0.0
static const double pi = 3.14159;

int main(void) {
    printf("e - %f\n", e);

    const int a; // contains garbage value

// ignore compiler error
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
    printf("a - %d\n", a);
#pragma clang diagnostic pop

    printf("pi - %f\n", pi);
    // cannot modify const variable
    // pi = 5;
}
