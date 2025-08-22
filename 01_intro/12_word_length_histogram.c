// print histogram of input word lengths between 1 and 10

#include <stdbool.h>
#include <stdio.h>

#define MAXLEN 10

int main(void) {
    int len = 0, counts[MAXLEN];
    bool in_word = false;

    for (int i = 0; i < MAXLEN; ++i)
        counts[i] = 0;

    for (int ch; (ch = getchar()) != EOF;) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (in_word && len < MAXLEN)
                ++counts[len - 1];
            len = 0;
            in_word = false;
        } else {
            ++len;
            in_word = true;
        }
    }

    printf("\nWord Length Histogram\n");
    for (int i = 0; i < MAXLEN; ++i) {
        printf("%3d ", i + 1);
        for (int j = 0; j < counts[i]; ++j)
            printf("=");
        printf("\n");
    }
    printf("\n");
}
