/*
    symbol table implementation using hash table
    collisions handled by chaining (new node is prepended)
*/

#include "str_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 5

struct node {
    struct node *next;
    char *name;
    char *val;
};

unsigned hash(char *name);
struct node *lookup(struct node *hash_table[], char *name);
struct node *define(struct node *hash_table[], char *name, char *val);
bool undefine(struct node *hash_table[], char *name);
void print_table(struct node *hash_table[]);
void clear_table(struct node *hash_table[]);

int main(void) {
    struct node *hash_table[HASH_TABLE_SIZE] = {NULL};
    struct node *cur;

    define(hash_table, "a", "10");
    define(hash_table, "b", "20");
    define(hash_table, "c", "30");
    define(hash_table, "x", "40");
    define(hash_table, "y", "50");
    define(hash_table, "z", "60");

    print_table(hash_table);
    printf("\n");

    if ((cur = lookup(hash_table, "x")))
        printf("x = %s\n", cur->val);
    if ((cur = lookup(hash_table, "a")))
        printf("a = %s\n", cur->val);

    // update existing entry
    define(hash_table, "y", "100");
    if ((cur = lookup(hash_table, "x")))
        printf("x = %s\n", cur->val);

    // lookup non-existent key
    if (!(cur = lookup(hash_table, "m")))
        printf("m not found\n");

    // delete non-existent key
    if (!undefine(hash_table, "n"))
        printf("n not found\n");

    // delete existing entry
    if (undefine(hash_table, "x"))
        printf("x deleted\n");

    printf("\n");
    print_table(hash_table);

    clear_table(hash_table);
}

// unsigned ensures hash val is non-negative
unsigned hash(char *s) {
    unsigned hash_val;
    for (hash_val = 0; *s; s++)
        hash_val = *s + (31 * hash_val);
    return hash_val % HASH_TABLE_SIZE;
}

struct node *lookup(struct node *hash_table[], char *name) {
    struct node *cur;
    // walk along linked list
    for (cur = hash_table[hash(name)]; cur; cur = cur->next)
        if ((str_cmp(cur->name, name, false)) == 0)
            return cur;
    return NULL;
}

struct node *define(struct node *hash_table[], char *name, char *val) {
    struct node *cur;
    unsigned hash_val;
    bool existing = false;

    if ((cur = lookup(hash_table, name))) {
        // name already in table
        // clear val
        free(cur->val);
        existing = true;
    } else {
        // name not in table
        cur = (struct node *)malloc(sizeof(*cur));

        // malloc failures
        if (!cur)
            return NULL;
        if (!(cur->name = str_dup(name))) {
            free(cur);
            return NULL;
        }

        // prepend node
        hash_val = hash(name);
        cur->next = hash_table[hash_val];
        hash_table[hash_val] = cur;
    }

    if (!(cur->val = str_dup(val))) {
        if (!existing) {
            free(cur->name);
            free(cur);
        }
        return NULL;
    }

    return cur;
}

bool undefine(struct node *hash_table[], char *name) {
    struct node *cur, *prev;
    unsigned hash_val = hash(name);

    prev = NULL;
    cur = hash_table[hash_val];
    while (cur) {
        if ((str_cmp(cur->name, name, false)) == 0) {
            // unlink node
            if (!prev)
                hash_table[hash_val] = cur->next;
            else
                prev->next = cur->next;

            // free node memory
            free(cur->name);
            free(cur->val);
            free(cur);
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void print_table(struct node *hash_table[]) {
    int i;
    struct node *cur;

    printf("Hash Table:\n");
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("%d -> ", i);
        for (cur = hash_table[i]; cur; cur = cur->next)
            printf("%s (%s) -> ", cur->name, cur->val);
        printf("null\n");
    }
}

void clear_table(struct node *hash_table[]) {
    int i;
    struct node *cur, *next;

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        cur = hash_table[i];
        while (cur) {
            next = cur->next;
            free(cur->name);
            free(cur->val);
            free(cur);
            cur = next;
        }
        hash_table[i] = NULL;
    }
}
