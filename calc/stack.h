#ifndef STACK_H
#define STACK_H

struct stack {
    float val;
    int oper;
    char *func;
    struct stack *next;
};

struct hash {
    char *func;
    int args;
    struct hash *next;
};

typedef struct stack s;
typedef struct hash  h;

s *create_stack_node(float val, int oper, char *func);
h *create_hash_node(char *func, int args);

void append(s **head, s **tail, s **node);

void push(s **head, s **node);
void hash_push(h **head, h **node);

s *pop(s **head);

h *find(h **head, char *str);

#endif  /* STACK_H */
