// print input word count

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int ch, words = 0;
    bool in_word = false;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            in_word = false;
        } else if (!in_word) {
            ++words;
            in_word = true;
        }
    }

    printf("%d words\n", words);
}
