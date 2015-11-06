#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

s *create_node(float val, int oper, char *func)
{
    s *new_node = (s*)malloc(sizeof(s));
    if (!new_node)
        return NULL;  // ERROR
    if (oper)
        new_node->oper = val;
    else if (func) {
	char *tempfunc = (char*)malloc(sizeof(func));
	sprintf(tempfunc, "%s", func);
	new_node->func = tempfunc;
	new_node->oper = 0;
    } else {
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
    if (!(*head))
	return NULL;  // ERROR
    s *temp = (*head);
    (*head) = (*head)->next;
    temp->next = NULL;
    return temp;
}
