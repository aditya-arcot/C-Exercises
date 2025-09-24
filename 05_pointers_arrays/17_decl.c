/*
    convert declarator to words
    e.g. char **argv[] -> argv: array of pointer to pointer to char

    simplified grammar
    ==================
    TYPE_DECL   -> TYPE DECL
    DECL        -> POINTER? DIR_DECL
    DIR_DECL    -> ID
                    | '(' DECL ')'
                    | DIR_DECL '()'
                    | DIR_DECL '[' NUM? ']'
    POINTER     -> '*' POINTER?
    ID          -> [a-zA-Z_]([a-zA-Z0-9_])*
    NUM         -> [0-9]+
    TYPE        -> 'int' | 'char' | 'float' | 'double' | 'void'
*/

#include "str_utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN 10
#define MAX_OUT 1000

enum TokenType { WORD, INTEGER, OPERATOR, NEWLINE, _EOF };

char token[MAX_TOKEN + 1];
char name[MAX_TOKEN + 1];
char data_type[MAX_TOKEN + 1];
char out[MAX_OUT + 1];

void parse_type_decl(void);
void parse_type(void);
void parse_decl(void);
int parse_pointer(void);
void parse_dir_decl(void);
void parse_dir_decl_suffix(void);

void out_str_cat(char *src);
void unget_token(void);
enum TokenType get_token(void);

int main(void) {
    while (1) {
        enum TokenType type = get_token();
        if (type == _EOF)
            break;
        if (type == NEWLINE)
            continue;
        unget_token();
        parse_type_decl();
        if (get_token() != NEWLINE) {
            printf("error: expected newline, got '%s'\n", token);
            exit(1);
        }
    }
}

void parse_type_decl(void) {
    parse_type();
    parse_decl();
    printf("%s: %s%s\n", name, out, data_type);
    out[0] = '\0';
}

void parse_type(void) {
    if (get_token() != WORD) {
        printf("error: expected data type, got '%s'\n", token);
        exit(1);
    }
    if (str_cmp(token, "int", false) != 0 && str_cmp(token, "char", false) != 0 &&
        str_cmp(token, "float", false) != 0 && str_cmp(token, "double", false) != 0 &&
        str_cmp(token, "void", false) != 0) {
        printf("error: unknown data type %s\n", token);
        exit(1);
    }
    str_copy(token, data_type);
}

void parse_decl(void) {
    int n_ptr = 0;
    if (get_token() == OPERATOR && token[0] == '*') {
        unget_token();
        n_ptr = parse_pointer();
        parse_dir_decl();
        while (n_ptr-- > 0)
            out_str_cat("pointer to ");
    } else {
        unget_token();
        parse_dir_decl();
    }
}

int parse_pointer(void) {
    if (get_token() != OPERATOR || token[0] != '*') {
        printf("error: expected '*', got '%s'\n", token);
        exit(1);
    }
    if (get_token() == OPERATOR && token[0] == '*') {
        unget_token();
        return 1 + parse_pointer();
    } else {
        unget_token();
        return 1;
    }
}

void parse_dir_decl(void) {
    enum TokenType type = get_token();
    if (type == WORD)
        str_copy(token, name);
    else if (type == OPERATOR && token[0] == '(') {
        parse_decl();
        if (get_token() != OPERATOR || token[0] != ')') {
            printf("error: expected ')', got '%s'\n", token);
            exit(1);
        }
    } else {
        printf("error: expected name or '(', got '%s'\n", token);
        exit(1);
    }
    parse_dir_decl_suffix();
}

void parse_dir_decl_suffix(void) {
    enum TokenType type = get_token();
    if (type == OPERATOR && token[0] == '(') {
        if (get_token() != OPERATOR || token[0] != ')') {
            printf("error: expected ')', got '%s'\n", token);
            exit(1);
        }
        parse_dir_decl_suffix();
        out_str_cat("function returning ");
    } else if (type == OPERATOR && token[0] == '[') {
        type = get_token();
        if (type == INTEGER) {
            char buf[MAX_TOKEN + 11];
            sprintf(buf, "array[%s] of ", token);
            if (get_token() != OPERATOR || token[0] != ']') {
                printf("error: expected ']', got '%s'\n", token);
                exit(1);
            }
            parse_dir_decl_suffix();
            out_str_cat(buf);
        } else if (type == OPERATOR && token[0] == ']') {
            parse_dir_decl_suffix();
            out_str_cat("array of ");
        } else {
            printf("error: expected number or ']', got '%s'\n", token);
            exit(1);
        }
    } else {
        unget_token();
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

enum TokenType get_token(void) {
    int ch;
    char *ptr = token;

    // skip tabs & spaces
    while (isblank(ch = getchar()))
        ;

    // word
    if (isalpha(ch)) {
        // id
        for (*ptr++ = ch; isalnum(ch = getchar()) || ch == '_';) {
            if (ptr - token >= MAX_TOKEN) {
                printf("error: token too long\n");
                exit(1);
            }
            *ptr++ = ch;
        }
        *ptr = '\0';
        ungetc(ch, stdin);
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
    if (ch == '*' || ch == '(' || ch == ')' || ch == '[' || ch == ']') {
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
