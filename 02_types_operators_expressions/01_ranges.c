#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void) {
    printf("char - signed by default\n");
    printf("------------------------\n");
    printf("signed char min:   %4d\n", SCHAR_MIN);
    printf("signed char max:   %4d\n", SCHAR_MAX);
    printf("char min:          %4d\n", CHAR_MIN);
    printf("char max:          %4d\n", CHAR_MAX);
    printf("unsigned char min: %4d\n", 0);
    printf("unsigned char max: %4d\n", UCHAR_MAX);
    printf("\n");

    printf("int - signed by default\n");
    printf("-----------------------\n");
    printf("short min:              %20d\n", SHRT_MIN);
    printf("short max:              %20d\n", SHRT_MAX);
    printf("int min:                %20d\n", INT_MIN);
    printf("int max:                %20d\n", INT_MAX);
    printf("long min:               %20ld\n", LONG_MIN);
    printf("long max:               %20ld\n", LONG_MAX);
    printf("long long min:          %20lld\n", LLONG_MIN);
    printf("long long max:          %20lld\n", LLONG_MAX);
    printf("unsigned short min:     %20u\n", 0);
    printf("unsigned short max:     %20u\n", USHRT_MAX);
    printf("unsigned int min:       %20u\n", 0);
    printf("unsigned int max:       %20u\n", UINT_MAX);
    printf("unsigned long min:      %20lu\n", 0UL);
    printf("unsigned long max:      %20lu\n", ULONG_MAX);
    printf("unsigned long long min: %20llu\n", 0ULL);
    printf("unsigned long long max: %20llu\n", ULLONG_MAX);
    printf("\n");

    printf("float\n");
    printf("-----\n");
    printf("float min:           %15.8e\n", (double)FLT_MIN);
    printf("float max:           %15.8e\n", (double)FLT_MAX);
    printf("float epsilon:       %15.8e\n", (double)FLT_EPSILON);
    printf("double min:          %15.8e\n", DBL_MIN);
    printf("double max:          %15.8e\n", DBL_MAX);
    printf("double epsilon:      %15.8e\n", DBL_EPSILON);
    printf("long double min:     %15.8Le\n", LDBL_MIN);
    printf("long double max:     %15.8Le\n", LDBL_MAX);
    printf("long double epsilon: %15.8Le\n", LDBL_EPSILON);
}
