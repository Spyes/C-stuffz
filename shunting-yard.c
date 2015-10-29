#include <stdio.h>
#include <stdlib.h>

struct stack {
    int val;
    int oper;
    struct stack *next;
};

typedef struct stack s;

s *create_node(int val, int oper)
{
    s *new_node = (s*)malloc(sizeof(s));
    if (!new_node)
        return NULL;
    new_node->val = val;
    new_node->oper = oper;
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

int isoper(int c)
{
    return (c == '+' || c == '-' ||
            c == '/' || c == '*');
}

int takes_precedence(int oper1, int oper2)
{
    return (oper1 == '*' || oper1 == '/')
        && (oper2 == '+' || oper2 == '-');
}

int equal_precedence(int oper1, int oper2)
{
    return (
            ((oper1 == '+' && oper2 == '-') ||
             (oper1 == '-' && oper2 == '+')) ||
            ((oper1 == '*' && oper2 == '/') ||
             (oper1 == '/' && oper2 == '*'))
            );
        
}

int main(int argc, char **argv)
{
    s *output = NULL,
        *output_tail = NULL,
        *operators = NULL,
        *n,
        *o;
    int input[7] = {1, '+', 2, '*', 3, '-', 4};
    int i;    

    for (i = 0; i < 7; i++) {
        n = create_node(input[i], isoper(input[i]));
        if (n->oper) {
            if (operators &&
                (takes_precedence(operators->val, n->val) ||
                 equal_precedence(operators->val, n->val))) {
                // bugged - actually should check precedence with all operators;
                o = pop(&operators);
                append(&output, &output_tail, &o);
            }            
            push(&operators, &n);
        }
        else
            append(&output, &output_tail, &n);
    }

    while (operators != NULL) {
        o = pop(&operators);
        append(&output, &output_tail, &o);
    }

    while (output != NULL) {
        if (output->oper)
            printf("%c\n", output->val);
        else
            printf("%i\n", output->val);
        output = output->next;
    }

    return 0;
}
