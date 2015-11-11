#include "reverse-polish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float power(float n, float b)
{
    if (b == 0) return 1;
    return n * power(n, b - 1);
}

float do_oper_calculation(int oper, float n1, float n2)
{
    if (oper == '+')
	return n1 + n2;
    else if (oper == '-')
	return n1 - n2;
    else if (oper == '*')
	return n1 * n2;
    else if (oper == '/')
	return n1 / n2;
    else if (oper == '^')
	return power(n1, n2);
}
/*
float do_func_calculation(char *func, float n1, float n2)
{
    if (strcmp(func, "max") == 0) {
	if (n1 > n2) return n1;
	return n2;
    }
}
*/
int func_args(char *func)
{
    if (strcmp(func, "max") == 0) return 2;
    if (strcmp(func, "sin") == 0) return 1;
}

int get_func_args_num(h **functions, char *func)
{
    h *f = find(functions, func);
    if (!f)
	return -1;  // ERROR! no such function
    return f->args;
}

s *pop_func_args(s **head, int amt)
{
    s *args_head,
	*temp;
    int i;
    for(i = 0; i < amt; i++) {
	temp = pop(head);
	temp->next = args_head;
	args_head = temp;
	free(head);
    }
    return args_head;
}

float reverse_polish_calculation(s **head, h **functions)
{
    s *curr, *temp;
    s *num_curr, *num_stack_head = NULL;
    h *f;
    s *n1, *n2;
    s *args_head;
    int num_of_args;
    float result;

    curr = (*head);
    while (curr) {
        if (curr->val) {
            num_curr = create_stack_node(curr->val, 0, NULL);
            push(&num_stack_head, &num_curr);
	    temp = curr->next;
	    free(curr);
	    curr = temp;
            continue;
        }

	n2 = pop(&num_stack_head);
	n1 = pop(&num_stack_head);
	
	if (curr->oper) {
	    result = do_oper_calculation(curr->oper, n1->val, n2->val);
	} else if (curr->func) {
	    if ((num_of_args = get_func_args_num(functions, curr->func)) == -1)
		return -1;  // ERROR! function doesn't exist
	    args_head = pop_func_args(&num_stack_head, num_of_args);
//	    result = do_func_calculation(curr->func);
	}

        num_curr = create_stack_node(result, 0, NULL);
        push(&num_stack_head, &num_curr);
	temp = curr->next;
	free(curr);
	curr = temp;
    }

    return num_curr->val;
}
