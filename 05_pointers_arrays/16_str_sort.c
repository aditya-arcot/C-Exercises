/*
    sort input lines lexicographically

    usage: sort [-n] [-r] [-f]
        -n numeric sort
        -r reverse sort
        -f fold upper and lower case together
*/

#include "line_utils.h"
#include "str_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 30

static char *line_ptrs[MAX_LINES];

int num_cmp(char *s, char *t, bool _);
void swap(void *v[], int i, int j);
void quick_sort(void *arr[], int left, int right, int (*cmp)(void *, void *, bool), bool reverse, bool fold);

int main(int argc, char *argv[]) {
    int ch, n_lines;
    bool numeric, reverse, fold;

    numeric = reverse = fold = false;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((ch = *++(argv[0])))
            switch (ch) {
            case 'n':
                numeric = true;
                break;
            case 'r':
                reverse = true;
                break;
            case 'f':
                fold = true;
                break;
            default:
                printf("Illegal option %c\n", ch);
                return 1;
            }

    if (fold && numeric) {
        printf("Error: -f and -n options are mutually exclusive\n");
        return 1;
    }

    n_lines = read_lines(line_ptrs, MAX_LINES);
    if (n_lines == ALLOC_ERR) {
        printf("Error: alloc failed\n");
        return 1;
    }
    if (n_lines == LINES_OVERFLOW)
        n_lines = MAX_LINES;
    // & is unnecessary for function name, like array names
    quick_sort((void **)line_ptrs, 0, n_lines - 1, (int (*)(void *, void *, bool))(numeric ? num_cmp : str_cmp),
               reverse, fold);
    write_lines(line_ptrs, n_lines);
}

// numeric comparison of strings representing numbers
int num_cmp(char *s, char *t, bool _) {
    double x, y;
    x = atof(s);
    y = atof(t);
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

// from 11_str_sort.c
// modified for generic array
void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// from 11_str_sort.c
// modifications - generic array, generic comparator, reverse option
// parentheses needed around *cmp in parameter list
void quick_sort(void *arr[], int left, int right, int (*cmp)(void *, void *, bool), bool reverse, bool fold) {
    int pivot, next_swap_idx;
    if (left >= right)
        return;
    pivot = right;
    next_swap_idx = left;
    for (int i = left; i < right; i++) {
        // cmp is function pointer
        // *cmp is function
        // (*cmp)(arr[i], arr[pivot]) is function call
        int res = (*cmp)(arr[i], arr[pivot], fold);
        if ((reverse && res > 0) || (!reverse && res < 0))
            swap(arr, next_swap_idx++, i);
    }
    swap(arr, pivot, next_swap_idx);
    pivot = next_swap_idx;
    quick_sort(arr, left, pivot - 1, cmp, reverse, fold);
    quick_sort(arr, pivot + 1, right, cmp, reverse, fold);
}
