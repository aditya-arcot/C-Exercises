#include <stdio.h>

enum Escape { BACKSPACE = '\b', TAB = '\t' };
enum Day { MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

int main(void) {
    enum Escape tab = TAB;
    printf("Tab - %d\n", tab);

    enum Day today = WEDNESDAY;
    printf("Today - %d\n", today);
}
