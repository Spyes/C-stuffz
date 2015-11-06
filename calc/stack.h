#ifndef STACK_H
#define STACK_H

struct stack {
    float val;
    int oper;
    char *func;
    struct stack *next;
};

typedef struct stack s;

s *create_node(float val, int oper, char *func);

void append(s **head, s **tail, s **node);

void push(s **head, s **node);

s *pop(s **head);

#endif  /* STACK_H */
