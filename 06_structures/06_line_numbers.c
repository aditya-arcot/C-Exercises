/*
    print line numbers of words in input
    uses binary tree to store words
*/

#include "debug_print.h"
#include "str_utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100

struct linked_list {
    int line_num;
    struct linked_list *next;
};

struct node {
    char *word;
    struct linked_list *line_nums;
    struct node *left;
    struct node *right;
};

struct node *add_word(struct node *node, char *word, int line_num);
struct linked_list *create_linked_list(void);
void add_line_num(struct node *node, int line_num);
struct node *create_node(void);
void print_tree(struct node *root);
int get_word(char *word, int max_len, int *line_num);

int main(void) {
    struct node *root = NULL;
    char word[MAX_WORD + 1];
    int line_num = 1;

    while (get_word(word, MAX_WORD, &line_num) != EOF)
        if (isalpha(word[0]))
            root = add_word(root, word, line_num);
    print_tree(root);
}

// adapted from 06_structures/04_count_words.c
// adds word to tree and updates line numbers
struct node *add_word(struct node *node, char *word, int line_num) {
    if (!node) {
        node = create_node();
        node->word = str_dup(word);
        node->line_nums = create_linked_list();
        node->line_nums->line_num = line_num;
        node->left = node->right = NULL;
        return node;
    }
    int cmp = str_cmp(word, node->word, false);
    if (cmp == 0) {
        // word already exists
        add_line_num(node, line_num);
    } else if (cmp < 0) {
        // add to left subtree
        node->left = add_word(node->left, word, line_num);
    } else {
        // add to right subtree
        node->right = add_word(node->right, word, line_num);
    }
    return node;
}

struct linked_list *create_linked_list(void) {
    return (struct linked_list *)malloc(sizeof(struct linked_list));
}

void add_line_num(struct node *node, int line_num) {
    struct linked_list *lst = node->line_nums;
    while (lst->next)
        lst = lst->next;
    if (lst->line_num != line_num) {
        lst->next = create_linked_list();
        lst->next->line_num = line_num;
    }
}

// from 06_structures/04_count_words.c
struct node *create_node(void) {
    return (struct node *)malloc(sizeof(struct node));
}

// adapted from 06_structures/04_count_words.c
void print_tree(struct node *node) {
    bool first = true;
    struct linked_list *lst;

    if (node) {
        print_tree(node->left);

        printf("%20s  ", node->word);
        for (lst = node->line_nums; lst; lst = lst->next) {
            if (!first)
                printf(", ");
            printf("%d", lst->line_num);
            first = false;
        }
        printf("\n");

        print_tree(node->right);
    }
}

// adapted from 06_structures/03_count_keywords.c
// reads word from input and tracks current line number
int get_word(char *word, int max_len, int *line_num) {
    int ch;
    char *word_ptr = word;

    while (isspace(ch = getchar()))
        if (ch == '\n')
            (*line_num)++;

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
                } else if (ch == '\n') {
                    (*line_num)++;
                }
            }
        }
        // inline comment
        else if (ch == '/') {
            if (--max_len > 0)
                *word_ptr++ = ch;
            // while ((ch = getchar()) != EOF && ch != '\n'
            while ((ch = getchar()) != EOF)
                if (ch == '\n') {
                    (*line_num)++;
                    break;
                }
        } else
            ungetc(ch, stdin);
    }

    *word_ptr = '\0';
    return word[0];
}
