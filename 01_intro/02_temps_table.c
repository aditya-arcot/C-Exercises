/*
    print Fahreheit-Celsius table
    for fahr = 0, 20, ..., 300
*/

#include <stdio.h>

// symbolic constants
#define LOWER 0
#define UPPER 300
#define STEP 20

double to_celsius(int fahr);

int main(void) {
    int fahr;
    // float celsius;
    // int lower, upper, step;

    // lower = 0;
    // upper = 300;
    // step = 20;

    // fahr = lower;
    // printf("%s %s\n", "Fahrenheit", "Celsius");
    // while (fahr <= upper)
    // {
    //     celsius = 5.0/9 * (fahr - 32);
    //     printf("%10d %7.1f\n", fahr, celsius);
    //     fahr = fahr + step;
    // }

    printf("%s %s\n", "Fahrenheit", "Celsius");
    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%10d %7.1f\n", fahr, to_celsius(fahr));
}

double to_celsius(int fahr) {
    return 5.0 / 9 * (fahr - 32);
}
