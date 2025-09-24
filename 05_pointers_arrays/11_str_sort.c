// sort input lines lexicographically

#include "alloc.h"
#include "debug_print.h"
#include "line_utils.h"
#include "str_utils.h"
#include <string.h>

#define MAX_LINES 10
#define MAX_LEN 1000
#define BUF_SIZE 10000
#define LINES_OVERFLOW -1
#define ALLOC_ERR -2

static char *line_ptrs[MAX_LINES];

void swap(char *v[], int i, int j);
void quick_sort(char *arr[], int left, int right);
int _read_lines(char *line_ptrs[], int max_lines);
void _write_lines(char *line_ptrs[], int n_lines);

int main(void) {
    int n_lines;
    n_lines = _read_lines(line_ptrs, MAX_LINES);
    if (n_lines == ALLOC_ERR) {
        printf("Error: alloc failed\n");
        return 1;
    }
    if (n_lines == LINES_OVERFLOW)
        n_lines = MAX_LINES;
    quick_sort(line_ptrs, 0, n_lines - 1);
    _write_lines(line_ptrs, n_lines);
}

// from 04_functions_program_structure/06_quicksort.c
// modified for string array
void swap(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// from 04_functions_program_structure/06_quicksort.c
// modified for string array
void quick_sort(char *arr[], int left, int right) {
    int pivot, next_swap_idx;
    if (left >= right)
        return;
    pivot = right;
    next_swap_idx = left;
    for (int i = left; i < right; i++)
        if (str_cmp(arr[i], arr[pivot], false) < 0)
            swap(arr, next_swap_idx++, i);
    swap(arr, pivot, next_swap_idx);
    pivot = next_swap_idx;
    quick_sort(arr, left, pivot - 1);
    quick_sort(arr, pivot + 1, right);
}

// reads lines & returns number of lines
// if too many lines, returns -1
int _read_lines(char *line_ptrs[], int max_lines) {
    int len, n_lines = 0;
    char *ptr, line[MAX_LEN + 1];
    while ((len = get_line(line, MAX_LEN, false, false)) > 0) {
        if (n_lines >= max_lines)
            return LINES_OVERFLOW;
        // 1 extra for null char
        ptr = alloc(len + 1);
        if (ptr == NULL)
            return ALLOC_ERR;
        str_copy(line, ptr);
        line_ptrs[n_lines++] = ptr;
    }
    return n_lines;
}

void _write_lines(char *line_ptrs[], int n_lines) {
    while (n_lines-- > 0)
        printf("%s\n", *line_ptrs++);
}
