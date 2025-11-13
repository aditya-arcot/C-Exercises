/*
    count word frequencies in input
    uses binary tree to store words
*/

#include "str_utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 100

struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

struct node *add_word(struct node *node, char *word);
struct node *create_node(void);
void print_tree(struct node *root);
int get_word(char *word, int max_len);

int main(void) {
    struct node *root = NULL;
    char word[MAX_WORD + 1];
    while (get_word(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            root = add_word(root, word);
    print_tree(root);
}

// add word to tree
struct node *add_word(struct node *node, char *word) {
    if (!node) {
        node = create_node();
        node->word = str_dup(word);
        node->count = 1;
        node->left = node->right = NULL;
        return node;
    }
    int cmp = str_cmp(word, node->word, false);
    if (cmp == 0) {
        // word already exists
        node->count++;
    } else if (cmp < 0) {
        // add to left subtree
        node->left = add_word(node->left, word);
    } else {
        // add to right subtree
        node->right = add_word(node->right, word);
    }
    return node;
}

struct node *create_node(void) {
    return (struct node *)malloc(sizeof(struct node));
}

void print_tree(struct node *node) {
    if (node) {
        print_tree(node->left);
        printf("%4d %s\n", node->count, node->word);
        print_tree(node->right);
    }
}

// from 06_structures/03_count_keywords.c
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
