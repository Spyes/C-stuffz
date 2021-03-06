#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "error.h"

s *create_stack_node(float val, int oper, char *func)
{
    s *new_node = (s*)malloc(sizeof(s));
    if (!new_node)
	quit_error("Couldn't create new node");
    if (oper) {
        new_node->oper = val;
	new_node->func = NULL;
	new_node->val = 0;
    } else if (func) {
	char *tempfunc = (char*)malloc(sizeof(func));
	sprintf(tempfunc, "%s", func);
	new_node->func = tempfunc;
	new_node->oper = 0;
	new_node->val = 0;
    } else {
        new_node->val = val;
        new_node->oper = 0;
	new_node->func = NULL;
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
	quit_error("Couldn't pop from stack");
    s *temp = (*head);
    (*head) = (*head)->next;
    temp->next = NULL;
    return temp;
}
