/*
    convert words to declarator
    e.g. argv is array of pointer to pointer to char -> char (*(*argv))

    uses same grammar as 17_decl.c
*/

#include "str_utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN 10
#define MAX_OUT 1000

enum TokenType { WORD, INTEGER, OPERATOR, NEWLINE, _EOF };

char token[MAX_TOKEN + 1];
char temp[MAX_OUT + 1];
char out[MAX_OUT + 1];

void out_str_cat(char *src);
void unget_token(void);
enum TokenType get_token(bool skip_words);

int main(void) {
    while (1) {
        enum TokenType type = get_token(false);
        if (type == _EOF)
            break;
        if (type == NEWLINE)
            continue;

        // name
        if (type != WORD) {
            printf("error: expected name, got '%s'\n", token);
            exit(1);
        }
        str_copy(token, out);

        while (1) {
            type = get_token(true);
            if (type == _EOF || type == NEWLINE) {
                printf("error: unexpected end of input\n");
                exit(1);
            }

            if (type == WORD) {
                if (str_cmp(token, "function", false) == 0) {
                    out_str_cat("()");
                } else if (str_cmp(token, "pointer", false) == 0) {
                    sprintf(temp, "(*%s)", out);
                    str_copy(temp, out);
                } else if (str_cmp(token, "array", false) == 0) {
                    if ((type = get_token(true)) == OPERATOR) {
                        if (token[0] != '[') {
                            printf("error: expected '[', got '%s'\n", token);
                            exit(1);
                        }
                        type = get_token(true);
                        if (type == INTEGER) {
                            out_str_cat("[");
                            out_str_cat(token);
                            out_str_cat("]");
                            if (get_token(true) != OPERATOR || token[0] != ']') {
                                printf("error: expected ']', got '%s'\n", token);
                                exit(1);
                            }
                        } else if (type == OPERATOR && token[0] == ']') {
                            out_str_cat("[]");
                        } else {
                            printf("error: expected array size or ']', got '%s'\n", token);
                            exit(1);
                        }
                    } else {
                        unget_token();
                    }
                } else if (str_cmp(token, "int", false) == 0 || str_cmp(token, "char", false) == 0 ||
                           str_cmp(token, "float", false) == 0 || str_cmp(token, "double", false) == 0 ||
                           str_cmp(token, "void", false) == 0) {
                    printf("%s %s\n", token, out);
                    break;
                } else {
                    printf("error: unexpected word '%s'\n", token);
                    exit(1);
                }
            } else {
                printf("error: unexpected token '%s'\n", token);
                exit(1);
            }
        }
        out[0] = '\0';
    }
}

void out_str_cat(char *src) {
    size_t out_len = strlen(out);
    size_t src_len = strlen(src);
    if (out_len + src_len > MAX_OUT) {
        printf("error: output buffer overflow\n");
        exit(1);
    }
    str_cat(src, out);
}

void unget_token(void) {
    for (int i = strlen(token) - 1; i >= 0; i--)
        ungetc(token[i], stdin);
}

enum TokenType get_token(bool skip_words) {
    int ch;
    char *ptr = token;

    // skip tabs & spaces
    while (isblank(ch = getchar()))
        ;

    // word
    if (isalpha(ch)) {
        for (*ptr++ = ch; isalnum(ch = getchar()) || ch == '_';) {
            if (ptr - token >= MAX_TOKEN) {
                printf("error: token too long\n");
                exit(1);
            }
            *ptr++ = ch;
        }
        *ptr = '\0';
        ungetc(ch, stdin);
        if (skip_words && (str_cmp(token, "is", false) == 0 || str_cmp(token, "of", false) == 0 ||
                           str_cmp(token, "to", false) == 0 || str_cmp(token, "returning", false) == 0)) {
            return get_token(skip_words);
        }
        return WORD;
    }

    // integer
    if (isdigit(ch)) {
        for (*ptr++ = ch; isdigit(ch = getchar());) {
            if (ptr - token >= MAX_TOKEN) {
                printf("error: token too long\n");
                exit(1);
            }
            *ptr++ = ch;
        }
        *ptr = '\0';
        ungetc(ch, stdin);
        return INTEGER;
    }

    // operator
    if (ch == '[' || ch == ']') {
        *ptr++ = ch;
        *ptr = '\0';
        return OPERATOR;
    }

    // newline
    if (ch == '\n') {
        *ptr++ = ch;
        *ptr = '\0';
        return NEWLINE;
    }

    if (ch == EOF) {
        *ptr++ = ch;
        *ptr = '\0';
        return _EOF;
    }

    printf("error: illegal character %c\n", ch);
    exit(1);
}
