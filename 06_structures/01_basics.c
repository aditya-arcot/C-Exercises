#include "debug_print.h"

// declaration with tag
struct point {
    int x;
    int y;
};

// definition & constant initialization
struct point pt1 = {10, 20};
// initialization by assignment illegal here
// struct point pt2 = pt1;

int main(void) {
    // member access
    pt1.x = 50;
    PRINT_INT(pt1.x);

    // declaration without tag
    struct {
        int x;
        int y;
    } pt2;
    PRINT_INT(pt2.x);

    // initialization by assignment allowed here
    struct point pt3 = pt1;
    PRINT_INT(pt3.x);

    // nested structure
    // inner braces optional here
    struct {
        struct point pt1;
        struct point pt2;
    } rect = {{10, 20}, {30, 40}};
    PRINT_INT(rect.pt1.x);
}
