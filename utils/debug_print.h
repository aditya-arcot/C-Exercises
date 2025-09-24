#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <stdbool.h>
#include <stdio.h>

#define PRINT_INT(int) printf(#int " = %d\n", int)
#define PRINT_LONG(lng) printf(#lng " = %ld\n", lng)
#define PRINT_BOOL(bool) printf(#bool " = %s\n", bool ? "true" : "false")
#define PRINT_STR(str) printf(#str " = \"%s\"\n", str)
#define PRINT_PTR(ptr) printf(#ptr " = %p\n", ptr)

#endif
