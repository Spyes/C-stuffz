#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

h *create_hash_node(char *func, int args)
{
    h *new_node = (h*)malloc(sizeof(h));
    char *tempfunc = (char*)malloc(sizeof(func));
    sprintf(tempfunc, "%s", func);
    new_node->func = tempfunc;
    new_node->args = args;
    new_node->next = NULL;
    return new_node;
}

void hash_push(h **head, h **node)
{
    (*node)->next = (*head);
    (*head) = (*node);
}

h *find(h **head, char *str)
{
    h *curr = (*head);
    while (curr) {
        if (strcmp(curr->func, str) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}
