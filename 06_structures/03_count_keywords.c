/*
    count C keyword frequencies in input
    includes array and pointer versions of binary search
*/
#include "str_utils.h"
#include <ctype.h>
#include <stdio.h>

#define MAX_WORD 100
#define N_KEYWORDS (sizeof keywords / sizeof(struct keyword_count))

struct keyword_count {
    char *keyword;
    int count;
} keywords[] = {{"auto", 0},     {"break", 0},  {"case", 0},    {"char", 0},   {"const", 0},    {"continue", 0},
                {"default", 0},  {"do", 0},     {"double", 0},  {"else", 0},   {"enum", 0},     {"extern", 0},
                {"float", 0},    {"for", 0},    {"goto", 0},    {"if", 0},     {"int", 0},      {"long", 0},
                {"register", 0}, {"return", 0}, {"short", 0},   {"signed", 0}, {"sizeof", 0},   {"static", 0},
                {"struct", 0},   {"switch", 0}, {"typedef", 0}, {"union", 0},  {"unsigned", 0}, {"void", 0},
                {"volatile", 0}, {"while", 0}};

int get_word(char *word, int max_len);
// int binary_search(char *word, struct keyword_count keywords[], int n);
struct keyword_count *binary_search(char *word, struct keyword_count *keywords, int n);

int main(void) {
    // int n;
    char word[MAX_WORD + 1];
    struct keyword_count *kc;
    // while (get_word(word, MAX_WORD) != EOF) {
    //     if (isalpha(word[0]))
    //         if ((n = binary_search(word, keywords, N_KEYWORDS)) >= 0)
    //             keywords[n].count++;
    // }
    while (get_word(word, MAX_WORD) != EOF) {
        if (isalpha(word[0]))
            if ((kc = binary_search(word, keywords, N_KEYWORDS)))
                kc->count++;
    }
    // for (unsigned long i = 0; i < N_KEYWORDS; i++)
    //     if (keywords[i].count > 0)
    //         printf("%4d %s\n", keywords[i].count, keywords[i].keyword);
    for (kc = &keywords[0]; kc < keywords + N_KEYWORDS; kc++)
        if (kc->count > 0)
            printf("%4d %s\n", kc->count, kc->keyword);
}

int get_word(char *word, int max_len) {
    int ch;
    char *word_ptr = word;

    while (isspace(ch = getchar()))
        ;

    if (ch == EOF) {
        *word_ptr = '\0';
        return EOF;
    }

    // ch contains first non-whitespace character
    *word_ptr++ = ch;

    // identifier or preprocessor directive
    if (isalpha(ch) || ch == '_' || ch == '#') {
        for (;;) {
            --max_len;
            ch = getchar();
            if (isalnum(ch) || ch == '_') {
                if (max_len > 0)
                    *word_ptr++ = ch;
            } else {
                ungetc(ch, stdin);
                break;
            }
        }
    }
    // string or character literal
    else if (ch == '\'' || ch == '\"') {
        int quote = ch;
        for (;;) {
            ch = getchar();
            if (ch == EOF)
                break;

            // ignore characters inside literal
            if (ch == '\\') {
                // skip escaped character
                ch = getchar();
            } else if (ch == quote) {
                // matching quote
                if (--max_len > 0)
                    *word_ptr++ = ch;
                break;
            }
        }
    }
    // comment
    else if (ch == '/') {
        // block comment
        if ((ch = getchar()) == '*') {
            if (--max_len > 0)
                *word_ptr++ = ch;
            // skip comment
            while ((ch = getchar()) != EOF) {
                if (ch == '*') {
                    if ((ch = getchar()) == '/') {
                        if (--max_len > 0)
                            *word_ptr++ = '*';
                        if (--max_len > 0)
                            *word_ptr++ = ch;
                        break;
                    } else
                        ungetc(ch, stdin);
                }
            }
        }
        // inline comment
        else if (ch == '/') {
            if (--max_len > 0)
                *word_ptr++ = ch;
            while ((ch = getchar()) != EOF && ch != '\n')
                ;
        } else
            ungetc(ch, stdin);
    }

    *word_ptr = '\0';
    return word[0];
}

// adapted from 03_control_flow/01_binary_search.c
// array version
// int binary_search(char *word, struct keyword_count keywords[], int n) {
//     for (int low = 0, high = n - 1; low <= high;) {
//         int mid = (low + high) / 2;
//         int cmp = str_cmp(word, keywords[mid].keyword, false);
//         if (cmp == 0)
//             return mid;
//         if (cmp < 0)
//             high = mid - 1;
//         else
//             low = mid + 1;
//     }
//     return -1;
// }

// pointer version
struct keyword_count *binary_search(char *word, struct keyword_count *keywords, int n) {
    struct keyword_count *low = &keywords[0];
    struct keyword_count *high = &keywords[n - 1];
    struct keyword_count *mid;
    while (low <= high) {
        // cannot do (low + high) / 2 with pointers
        // addition of pointers is not defined
        mid = low + (high - low) / 2;
        int cmp = str_cmp(word, mid->keyword, false);
        if (cmp == 0)
            return mid;
        if (cmp < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return NULL;
}
