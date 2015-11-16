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

float do_func_calculation(char *func, s **args_head)
{
    if (strcmp(func, "max") == 0) {
	int n1 = pop(args_head)->val;
	int n2 = pop(args_head)->val;
	if (n1 > n2)
	    return n1;
	return n2;
    } else if (strcmp(func, "exp") == 0) {
	int n1 = pop(args_head)->val;
	return power(2.71828, n1);
    }
}

int get_func_args_num(s **functions_hash, char *func)
{
    s *f = find(functions_hash, func);
    if (!f)
	return -1;
    return (int)f->val;
}

s *pop_func_args(s **head, int amt)
{
    s *args_head = NULL,
	*temp;
    int i;
    for(i = 0; i < amt; i++) {
	temp = pop(head);
	temp->next = args_head;
	args_head = temp;
	//free(head);
    }
    return args_head;
}

float reverse_polish_calculation(s **head, s **functions_hash)
{
    s *curr, *temp;
    s *num_curr, *num_stack_head = NULL;
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
	    //free(curr);
	    curr = temp;
            continue;
        }
	
	if (curr->oper) {
	    n2 = pop(&num_stack_head);
	    n1 = pop(&num_stack_head);
	    result = do_oper_calculation(curr->oper, n1->val, n2->val);
	} else if (curr->func) {
	    if ((num_of_args = get_func_args_num(functions_hash, curr->func)) == -1)
	    	return -1;  // ERROR! function doesn't exist
	    args_head = pop_func_args(&num_stack_head, num_of_args);
	    result = do_func_calculation(curr->func, &args_head);
	}

        num_curr = create_stack_node(result, 0, NULL);
        push(&num_stack_head, &num_curr);
	temp = curr->next;
	//free(curr);
	curr = temp;
    }

    return num_curr->val;
}
