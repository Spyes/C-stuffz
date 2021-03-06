#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

s *create_hash_node(char *func, int args)
{
    s *new_node = (s*)malloc(sizeof(s));
    new_node->func = func;
    new_node->val = args;
    new_node->oper = 0;
    new_node->next = NULL;
    return new_node;
}

int hash_string_function(char *str)
{
    int hashVal = 0;
    int ch, i;
    for (i = 0, ch = str[i]; ch != '\0'; i++, ch = str[i])
	hashVal = (hashVal * 27 + (ch - '0')) % HASH_SIZE;
    return hashVal;
}

void insert(s **hash_table, s **node)
{
    int k = hash_string_function((*node)->func);
    if (hash_table[k] == NULL)
	hash_table[k] = (*node);
    else {
	s *cur = hash_table[k];
	while (cur->next != NULL)
	    cur = cur->next;
	cur->next = (*node);
    }
}

s *find(s **hash_table, char *key)
{
    int k = hash_string_function(key);
    s *curr = hash_table[k];
    while (curr) {
	if (strcmp(curr->func, key) == 0)
	    return curr;
	curr = curr->next;
    }
    return NULL;
}
