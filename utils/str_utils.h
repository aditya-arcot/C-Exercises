#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>

void str_rev(char s[]);
void str_copy(char *s, char *t);
int str_cmp(char *s, char *t, bool fold);
void str_cat(char *s, char *t);

#endif
