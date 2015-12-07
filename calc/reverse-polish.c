#include "reverse-polish.h"
#include "error.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

s *num_stack_head = NULL;

void cleanup_calc()
{
    s *cur, *temp;
    cur = num_stack_head;
    while (cur) {
	temp = cur->next;
	free(cur);
	cur = temp;
    }
}

float do_oper_calculation(int oper)
{
    s *temp;
    temp = pop(&num_stack_head);
    float n2 = temp->val;
    free(temp);
    temp = pop(&num_stack_head);
    float n1 = temp->val;
    free(temp);

    if (oper == '+')
	return n1 + n2;
    else if (oper == '-')
	return n1 - n2;
    else if (oper == '*')
	return n1 * n2;
    else if (oper == '/')
	return n1 / n2;
    else if (oper == '^')
	return pow(n1, n2);
}

float do_func_calculation(char *func, s **args_head)
{
    s *temp;
    if (strcmp(func, "max") == 0) {
	temp = pop(args_head);
	float n1 = temp->val;
	free(temp);
	temp = pop(args_head);
	float n2 = temp->val;
	free(temp);
	if (n1 > n2)
	    return n1;
	return n2;
    } else if (strcmp(func, "exp") == 0) {
	temp = pop(args_head);
	float n1 = temp->val;
	free(temp);
	return pow(2.71828, n1);
    } else if (strcmp(func, "quit") == 0) {
	cleanup_calc();
	quit_elegantly();
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
    }
    return args_head;
}

float reverse_polish_calculation(s **head, s **functions_hash)
{
    s *curr, *temp;
    s *num_curr;
    s *n1, *n2;
    s *args_head;
    int num_of_args;
    float result;
    num_stack_head = NULL;

    curr = (*head);
    while (curr) {
        if (curr->val) {
            num_curr = create_stack_node(curr->val, 0, NULL);
            push(&num_stack_head, &num_curr);
	    curr = curr->next;
            continue;
        }
	
	if (curr->oper) {
	    result = do_oper_calculation(curr->oper);
	} else if (curr->func) {
	    if ((num_of_args = get_func_args_num(functions_hash, curr->func)) == -1)
		error("Function doesn't exist");
	    args_head = pop_func_args(&num_stack_head, num_of_args);
	    result = do_func_calculation(curr->func, &args_head);
	}

        num_curr = create_stack_node(result, 0, NULL);
        push(&num_stack_head, &num_curr);
	curr = curr->next;
    }

    float val = num_curr->val;
    cleanup_calc();
    return val;
}
