#include <stdio.h>

/*
    print Fahreheit-Celsius table
    for fahr = 0, 20, ..., 300
*/

// symbolic constants
#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{
    int fahr;
    // float celsius;
    // int lower, upper, step;

    // lower = 0;
    // upper = 300;
    // step = 20;

    printf("%s %s\n", "Fahrenheit", "Celsius");

    // fahr = lower;
    // while (fahr <= upper)
    // {
    //     celsius = 5.0/9 * (fahr - 32);
    //     printf("%10d %7.1f\n", fahr, celsius);
    //     fahr = fahr + step;
    // }

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
        printf("%10d %7.1f\n", fahr, (5.0 / 9) * (fahr - 32));
}