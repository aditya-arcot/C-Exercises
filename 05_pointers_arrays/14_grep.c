/*
    simple grep program

    usage: grep [-n] [-x] pattern
        -x invert match
        -n print line numbers
*/

#include "debug_print.h"
#include "line_utils.h"
#include <string.h>

#define MAX_LEN 1000

int main(int argc, char *argv[]) {
    bool invert, print_line, found;
    int ch;
    long line_num;
    char line[MAX_LEN + 1];

    invert = print_line = false;
    while (--argc > 0 && (*++argv)[0] == '-') // first char of next arg string
        // allows combined args
        while ((ch = *++(argv[0]))) // start at second char of arg string
            switch (ch) {
            case 'x':
                invert = true;
                break;
            case 'n':
                print_line = true;
                break;
            default:
                printf("Illegal option %c\n", ch);
                return 1;
            }

    if (argc != 1) {
        printf("Usage: grep [-n] [-x] pattern\n");
        return 1;
    }

    found = false;
    line_num = 0;
    while (get_line(line, MAX_LEN, false, false) > 0) {
        line_num++;
        // first idx of pattern
        if ((strstr(line, *argv) != NULL) != invert) {
            if (print_line)
                printf("%ld: ", line_num);
            printf("%s\n", line);
            found = true;
        }
    }
    return found ? 0 : 1;
}
