#ifndef STACK_H
#define STACK_H

#define HASH_SIZE 13

struct stack {
    float val;
    int oper;
    char *func;
    struct stack *next;
};

typedef struct stack s;

s *create_stack_node(float val, int oper, char *func);

void append(s **head, s **tail, s **node);

void push(s **head, s **node);

s *pop(s **head);

s *create_hash_node(char *func, int args);

void insert(s **hash_table, s **node);

s *find(s **hash_table, char *key);

#endif  /* STACK_H */
