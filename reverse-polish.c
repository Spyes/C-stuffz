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
        
        temp = (s*)malloc(sizeof(s));
        temp->val = 3;
        temp->oper = 0;
        temp->next = NULL;
        (*tail)->next = temp;
        (*tail) = temp;
        
        temp = (s*)malloc(sizeof(s));
        temp->val = '+';
        temp->oper = 1;
        (*tail)->next = temp;
        temp->next = NULL;
        (*tail) = temp;

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
    tail = NULL;
    num_stack_head = NULL;
    //num_stack_tail = NULL;
    // 5 + ((1 + 2) * 4) - 3
    // 5 1 2 + 4 * + 3 -
    int size = init(&head, &tail, &curr, 1);

    int n1, n2;
    int result;
    curr = head;

    while (curr != NULL) {
        printf("val=%i oper=%i\n", curr->val, curr->oper);
        curr = curr->next;
        
        /*
        if (!curr->oper) {
            num_curr = pop(&head);
            num_curr->next = num_stack_head;
            num_stack_head = num_curr;
            continue;
        }

        if (curr->val == '+') {
            n1 = pop(&num_stack_head);
            n2 = pop(&num_stack_head);
            result = n1 + n2;
            num_curr = (s*)malloc(sizeof(s));
            num_curr->val = result;
            num_curr->oper = 0;
            num_curr->next = num_stack_head;
        }
        
        curr = curr->next;*/
    }

    return 0;
}
