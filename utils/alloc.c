#include <stdio.h>

#define BUFSIZE 10000

static char buf[BUFSIZE];
static char *alloc_ptr = buf;

/*
allocates n chars & returns pointer to first char
from 05_pointers_arrays/06_alloc_buf.c

params:
    n - number of chars to allocate

returns:
    pointer to first char or NULL if not enough space
*/
char *alloc(int n) {
    if (buf + BUFSIZE - alloc_ptr >= n) {
        // enough space
        alloc_ptr += n;
        return alloc_ptr - n; // old p
    } else {
        // not enough space
        // 0 is never valid data address
        return NULL;
    }
}

/*
frees storage pointed to by p
from 05_pointers_arrays/06_alloc_buf.c
*/
void afree(char *p) {
    if (p >= buf && p < buf + BUFSIZE)
        alloc_ptr = p;
}
