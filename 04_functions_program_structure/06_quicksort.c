// recursive quick sort algorithm using right pivot

#include <stdio.h>

void quick_sort(int arr[], int left, int right);
void swap(int v[], int i, int j);
void print(int arr[], int length);

int main(void)
{
    int arr[] = {2, 6, 1, 3, 7, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, 0, size - 1);
    print(arr, size);
}

void quick_sort(int arr[], int left, int right)
{
    int pivot, next_swap_idx;

    // 2 or less elements
    if (left >= right)
        return;

    // use right element as pivot
    pivot = right;

    next_swap_idx = left;

    // create left partition by swapping
    for (int i = left; i < right; i++)
        if (arr[i] < arr[pivot])
            swap(arr, next_swap_idx++, i);

    // move pivot between partitions
    swap(arr, pivot, next_swap_idx);
    pivot = next_swap_idx;

    quick_sort(arr, left, pivot - 1);  // sort left partition
    quick_sort(arr, pivot + 1, right); // sort right partition
}

void swap(int v[], int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
