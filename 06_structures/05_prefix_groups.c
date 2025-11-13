/*
    print words with common prefix from input
    uses binary tree to store words

    usage: prefix_groups [prefix_length]
        prefix_length: length of common prefix (default 6)
*/

#include "str_utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100

struct node {
    char *word;
    bool prefix_match;
    struct node *left;
    struct node *right;
};

int compare(char *s, struct node *node, size_t prefix, bool *prefix_match);
struct node *add_word(struct node *node, char *word, size_t prefix, bool *prefix_match);
struct node *create_node(void);
void print_tree(struct node *root);
int get_word(char *word, int max_len);

int main(int argc, char *argv[]) {
    struct node *root = NULL;
    char word[MAX_WORD + 1];
    size_t prefix = (size_t)6;
    bool prefix_match = false;

    if (argc > 1)
        prefix = (size_t)atoi(argv[1]);
    while (get_word(word, MAX_WORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= prefix)
            root = add_word(root, word, prefix, &prefix_match);
        prefix_match = false;
    }
    print_tree(root);
}

int compare(char *s, struct node *node, size_t prefix, bool *prefix_match) {
    size_t i;
    char *t = node->word;
    for (i = 0; *s == *t; s++, t++, i++)
        if (!*s)
            return 0;
    if (i >= prefix) {
        // identical in prefix length
        *prefix_match = true;
        node->prefix_match = true;
    }
    return *s - *t;
}

// adapted from 06_structures/04_count_words.c
// adds word to tree and tracks prefix matches
struct node *add_word(struct node *node, char *word, size_t prefix, bool *prefix_match) {
    if (!node) {
        node = create_node();
        node->word = str_dup(word);
        node->prefix_match = *prefix_match;
        node->left = node->right = NULL;
        return node;
    }
    int cmp = compare(word, node, prefix, prefix_match);
    if (cmp < 0) {
        // add to left subtree
        node->left = add_word(node->left, word, prefix, prefix_match);
    } else if (cmp > 0) {
        // add to right subtree
        node->right = add_word(node->right, word, prefix, prefix_match);
    }
    return node;
}

// from 06_structures/04_count_words.c
struct node *create_node(void) {
    return (struct node *)malloc(sizeof(struct node));
}

// adapted from 06_structures/04_count_words.c
// prints only words that have prefix matches
void print_tree(struct node *node) {
    if (node) {
        print_tree(node->left);
        if (node->prefix_match)
            printf("%s\n", node->word);
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
