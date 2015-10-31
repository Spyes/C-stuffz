#include "reverse-polish.h"
#include <stdio.h>

float reverse_polish_calculation(s **head)
{
    s *curr;
    s *num_curr, *num_stack_head = NULL;
    s *n1, *n2;
    float result;

    curr = (*head);
    while (curr) {
        if (!curr->oper) {
            num_curr = create_node(curr->val, 0);
            push(&num_stack_head, &num_curr);
            curr = curr->next;
            continue;
        }

        // it is an operator
        n2 = pop(&num_stack_head);
        n1 = pop(&num_stack_head);

        if (!n1 || !n2)
            return 1;
        if (curr->oper == '+')
            result = n1->val + n2->val;
        else if (curr->oper == '-')
            result = n1->val - n2->val;
        else if (curr->oper == '*')
            result = n1->val * n2->val;
        else if (curr->oper == '/')
            result = n1->val / n2->val;

        num_curr = create_node(result, 0);
        push(&num_stack_head, &num_curr);

        curr = curr->next;
    }

    return num_curr->val;
}
