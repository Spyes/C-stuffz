#ifndef STACK_H
#define STACK_H

struct stack {
    int val;
    int oper;
    struct stack *next;
};

typedef struct stack s;

s *create_node(int val, int oper);

void append(s **head, s **tail, s **node);

void push(s **head, s **node);

s *pop(s **head);

#endif  /* STACK_H */
