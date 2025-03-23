// print histogram of input word lengths between 1 and 10

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAXLEN 10

int main(void) {
    int ch, len = 0, in_word = FALSE;
    int counts[MAXLEN];

    for (int i = 0; i < MAXLEN; ++i)
        counts[i] = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (in_word && len < MAXLEN)
                ++counts[len - 1];
            len = 0;
            in_word = FALSE;
        } else {
            ++len;
            in_word = TRUE;
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
