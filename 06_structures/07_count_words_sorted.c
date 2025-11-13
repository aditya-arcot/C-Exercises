// count word frequencies in input and output in order of frequency

#include "str_utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD 100
#define MAX_NODES 100

struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

struct node *add_word(struct node *node, char *word);
struct node *create_node(void);
void create_node_list(struct node *node, int *n_nodes, struct node node_lst[], int max_len);
void swap_nodes(struct node nodes[], int i, int j);
void sort_node_list(struct node nodes[], int left, int right);
int get_word(char *word, int max_len);

int main(void) {
    struct node *root = NULL;
    char word[MAX_WORD + 1];
    struct node node_lst[MAX_NODES];
    int nodes = 0;

    while (get_word(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            root = add_word(root, word);

    create_node_list(root, &nodes, node_lst, MAX_NODES);
    sort_node_list(node_lst, 0, nodes - 1);

    for (int i = 0; i < nodes; i++)
        printf("%4d %s\n", node_lst[i].count, node_lst[i].word);
}

// from 06_structures/04_count_words.c
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

// from 06_structures/04_count_words.c
struct node *create_node(void) {
    return (struct node *)malloc(sizeof(struct node));
}

void create_node_list(struct node *node, int *n_nodes, struct node node_lst[], int max_len) {
    if (*n_nodes >= max_len)
        return;
    if (node) {
        create_node_list(node->left, n_nodes, node_lst, max_len);
        node_lst[*n_nodes].word = str_dup(node->word);
        node_lst[*n_nodes].count = node->count;
        (*n_nodes)++;
        create_node_list(node->right, n_nodes, node_lst, max_len);
    }
}

// from 04_functions_program_structure/06_quicksort.c
// modified for node array
void swap_nodes(struct node nodes[], int i, int j) {
    struct node temp = nodes[i];
    nodes[i] = nodes[j];
    nodes[j] = temp;
}

// from 04_functions_program_structure/06_quicksort.c
// modified for node array
void sort_node_list(struct node nodes[], int left, int right) {
    int pivot, next_swap_idx;
    if (left >= right)
        return;
    pivot = right;
    next_swap_idx = left;
    for (int i = left; i < right; i++)
        if (nodes[i].count > nodes[pivot].count) // descending
            swap_nodes(nodes, next_swap_idx++, i);
    swap_nodes(nodes, pivot, next_swap_idx);
    pivot = next_swap_idx;
    sort_node_list(nodes, left, pivot - 1);
    sort_node_list(nodes, pivot + 1, right);
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
