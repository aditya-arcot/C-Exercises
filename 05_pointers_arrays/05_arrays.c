#include "debug_print.h"

// equivalent
void f(char *s);
void f(char s[]);

int main(void) {
    int *p_arr, x;
    int arr[3] = {10, 20, 30};
    char ch_arr[] = "xyz";

    // width (bytes) of int in arr
    PRINT_LONG(sizeof(arr[0]));
    printf("\n");

    p_arr = arr;

    // equivalent
    // arr[i] == *(arr + i) == *(p_arr + i) == p_arr[i]
    PRINT_PTR((void *)&arr[1]);
    PRINT_PTR((void *)(arr + 1));
    PRINT_PTR((void *)(p_arr + 1));
    PRINT_PTR((void *)&p_arr[1]);
    printf("\n");

    // set x to copy of arr[2]
    x = *(p_arr + 2);
    PRINT_INT(x);

    // x is not affected by changing arr[2] or p_arr
    arr[2] = 50;
    ++p_arr;
    PRINT_INT(x);
    printf("\n");

    // illegal
    // ++arr;

    f("abc");
    f(ch_arr);
}

void f(char *s) {
    // modifying s does not modify arr in caller
    s++;
    PRINT_STR(s);
}
