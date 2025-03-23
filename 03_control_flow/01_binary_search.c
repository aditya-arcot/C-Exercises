// binary search for int x in sorted array arr of length n

#include <stdio.h>

int binary_search(int x, int arr[], int n);

int main(void) {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    int test_cases[] = {7, 1, 15, 8, 11, 0};
    int test_size = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < test_size; i++)
        printf("%d\t%d\n", test_cases[i], binary_search(test_cases[i], arr, n));
}

int binary_search(int x, int arr[], int n) {
    int low = 0, mid, high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x == arr[mid])
            return mid;
        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}
