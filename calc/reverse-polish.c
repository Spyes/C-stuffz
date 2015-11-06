#include "reverse-polish.h"
#include <stdio.h>
#include <stdlib.h>

float power(float n, float b)
{
    if (b == 0) return 1;
    return n * power(n, b - 1);
}

float do_calculation(int oper, float n1, float n2)
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

float reverse_polish_calculation(s **head)
{
    s *curr, *temp;
    s *num_curr, *num_stack_head = NULL;
    s *n1, *n2;
    float result;

    curr = (*head);
    while (curr) {
        if (!curr->oper) {
            num_curr = create_node(curr->val, 0);
            push(&num_stack_head, &num_curr);
	    temp = curr->next;
	    free(curr);
	    curr = temp;
            continue;
        }

        n2 = pop(&num_stack_head);
        n1 = pop(&num_stack_head);
        if (!n1 || !n2)
            return -1; // not enough values in stack - ERROR
	result = do_calculation(curr->oper, n1->val, n2->val);
        num_curr = create_node(result, 0);
        push(&num_stack_head, &num_curr);
	temp = curr->next;
	free(curr);
	curr = temp;
    }

    return num_curr->val;
}
