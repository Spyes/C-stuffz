#include <stdio.h>
#include <stdlib.h>

struct stack {
    int val;
    int oper;
    struct stack *next;
};
typedef struct stack s;

int init(s **head, s **tail, s **curr, int small)
{
    s *temp;
    if (small) {
        (*curr) = (s*)malloc(sizeof(s));
        (*curr)->val = 4;
        (*curr)->oper = 0;
        (*curr)->next = NULL;
        (*head) = (*curr);
        (*tail) = (*curr);
        
        (*curr) = (s*)malloc(sizeof(s));
        (*curr)->val = 3;
        (*curr)->oper = 0;
        (*curr)->next = NULL;
        (*tail)->next = (*curr);
        (*tail) = (*curr);
        
        (*curr) = (s*)malloc(sizeof(s));
        (*curr)->val = '+';
        (*curr)->oper = 1;
        (*tail)->next = (*curr);
        (*curr)->next = NULL;
        (*tail) = (*curr);

        return 2;
    }
    int size = 0;
    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = 5;
    (*curr)->oper = 0;
    (*head) = (*curr);
    (*tail) = (*curr);
    size++;

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = 1;
    (*curr)->oper = 0;
    (*tail)->next = (*curr);
    (*tail) = (*curr);
    size++;

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = 2;
    (*curr)->oper = 0;
    (*tail)->next = (*curr);
    (*tail) = (*curr);
    size++;

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = '+';
    (*curr)->oper = 1;
    (*tail)->next = (*curr);
    (*tail) = (*curr);

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = 4;
    (*curr)->oper = 0;
    (*tail)->next = (*curr);
    (*tail) = (*curr);
    size++;

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = '*';
    (*curr)->oper = 1;
    (*tail)->next = (*curr);
    (*tail) = (*curr);

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = '+';
    (*curr)->oper = 1;
    (*tail)->next = (*curr);
    (*tail) = (*curr);

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = 3;
    (*curr)->oper = 0;
    (*tail)->next = (*curr);
    (*tail) = (*curr);
    size++;

    (*curr) = (s*)malloc(sizeof(s));
    (*curr)->val = '-';
    (*curr)->oper = 1;
    (*tail)->next = (*curr);
    (*tail) = (*curr);

    return size;
}

s *pop(s ** head)
{
    s * next_node = NULL;
    if (*head == NULL)
        return NULL;

    next_node = (*head)->next;
    s *ret = *head;
    *head = next_node;
    return ret;
}

int main(int argc, char **argv)
{
    s *head, *tail, *curr;
    s *num_curr, *num_stack_head;//, *num_stack_tail;
    s *n1, *n2;
    tail = NULL;
    num_stack_head = NULL;
    //num_stack_tail = NULL;
    // 5 + ((1 + 2) * 4) - 3
    // 5 1 2 + 4 * + 3 -
    int size = init(&head, &tail, &curr, 0);

    int result;
    curr = head;

    while (1) {
        if (!curr->oper) {
            num_curr = (s*)malloc(sizeof(s));
            num_curr->val = curr->val;
            num_curr->oper = 0;
            num_curr->next = num_stack_head;
            num_stack_head = num_curr;
            curr = curr->next;
            continue;
        }

        // it is an operator
        n2 = pop(&num_stack_head);
        n1 = pop(&num_stack_head);

        if (!n1 || !n2)
            return 1;
        if (curr->val == '+')
            result = n1->val + n2->val;
        else if (curr->val == '-')
            result = n1->val - n2->val;
        else if (curr->val == '*')
            result = n1->val * n2->val;
        else if (curr->val == '/')
            result = n1->val / n2->val;
        num_curr = (s*)malloc(sizeof(s));
        num_curr->val = result;
        num_curr->oper = 0;
        num_curr->next = num_stack_head;
        num_stack_head = num_curr;

        if (curr->next == NULL)
            break;
        curr = curr->next;
    }

    printf("%i\n", num_curr->val);
    return 0;
}
