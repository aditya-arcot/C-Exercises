/*
    stack-based memory allocator

    afree must be called in reverse order of alloc
*/

#include "debug_print.h"

#define BUFSIZE 100

// storage for alloc
static char buf[BUFSIZE];
// next free position
static char *alloc_ptr = buf;

char *alloc(int n);
void afree(char *p);

int main(void) {
    char *p;
    // allocate 80
    p = alloc(80);
    PRINT_LONG(p - buf);
    // allocate 20
    p = alloc(20);
    PRINT_LONG(p - buf);
    // free last 20
    afree(p);
    // allocate 25
    // not enough space
    p = alloc(25);
    PRINT_LONG(p - buf);
}

// return pointer to n chars or 0 if not enough space
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

// free storage pointed to by p
void afree(char *p) {
    if (p >= buf && p < buf + BUFSIZE)
        alloc_ptr = p;
}
