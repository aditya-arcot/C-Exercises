#include "debug_print.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
    int x;
    int y;
};
struct rect {
    struct point pt1;
    struct point pt2;
};

struct point make_pt(int x, int y);
struct point add_points(struct point pt1, struct point pt2);
struct rect canonize_rect(struct rect r);
bool pt_in_rect(struct point pt, struct rect r);

int main(void) {
    struct rect screen = {make_pt(0, 0), make_pt(100, 100)};
    PRINT_INT(screen.pt1.x);
    PRINT_INT(screen.pt2.y);

    struct rect *screen_ptr = &screen;
    PRINT_INT((*screen_ptr).pt1.x);
    PRINT_INT(screen_ptr->pt1.x);
}

struct point make_pt(int x, int y) {
    // struct point pt;
    // pt.x = x - 1;
    // pt.y = y + 1;
    // return pt;
    return (struct point){x - 1, y + 1};
}

struct point add_points(struct point pt1, struct point pt2) {
    return (struct point){pt1.x + pt2.x, pt1.y + pt2.y};
}

// ensure pt1 is bottom-left, pt2 is top-right
// (0, 0) is bottom-left
struct rect canonize_rect(struct rect r) {
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

// rect includes bottom & left edge, excludes top & right edge
bool pt_in_rect(struct point pt, struct rect r) {
    r = canonize_rect(r);
    return pt.x >= r.pt1.x && pt.x < r.pt2.x && pt.y >= r.pt1.y && pt.y < r.pt2.y;
}
