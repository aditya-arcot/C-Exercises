#include <stdio.h>

const double e; // initialized to 0.0
const double pi = 3.14159;

int main(void) {
    printf("e - %f\n", e);

    const int a; // contains garbage value
    printf("a - %d\n", a);

    printf("pi - %f\n", pi);
    // cannot modify a const variable
    pi = 5;
}
