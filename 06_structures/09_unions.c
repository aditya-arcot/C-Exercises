#include <stdio.h>

union Data {
    int i;
    float f;
    char c;
};

int main(void) {
    // must be initialized with type of first member
    union Data data = {10};

    // only last assigned member holds valid, predictable value
    printf("After initializing data.i to 10:\n");
    printf("data.i = %d\n", data.i);
    printf("data.f = %f\n", data.f);
    printf("data.c = %c\n", data.c);
    printf("\n");

    data.f = 3.14;
    printf("After assigning to data.f:\n");
    printf("data.i = %d\n", data.i);
    printf("data.f = %f\n", data.f);
    printf("data.c = %c\n", data.c);
    printf("\n");

    data.c = 'A';
    printf("After assigning to data.c:\n");
    printf("data.i = %d\n", data.i);
    printf("data.f = %f\n", data.f);
    printf("data.c = %c\n", data.c);
}
