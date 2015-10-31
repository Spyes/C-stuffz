#include <stdlib.h>
#include "stack.h"

s *create_node(float val, int oper)
{
    s *new_node = (s*)malloc(sizeof(s));
    if (!new_node)
        return NULL;
    if (oper)
        new_node->oper = val;
    else {
        new_node->val = val;
        new_node->oper = 0;
    }
    new_node->next = NULL;
    return new_node;
}

void append(s **head, s **tail, s **node)
{
    if (!(*head))
        (*head) = (*node);
    if ((*tail))
        (*tail)->next = (*node);
    (*tail) = (*node);
}

void push(s **head, s **node)
{
    (*node)->next = (*head);
    (*head) = (*node);
}

s *pop(s **head)
{
    s *temp = (*head);
    (*head) = (*head)->next;
    temp->next = NULL;
    return temp;
}