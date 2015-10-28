#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct stack {
    int value;
    int oper;   // boolean
    struct stack *next;
};

typedef struct stack stack;


int main(int argc, char **argv)
{
    int ch;
    stack *output_stack = NULL;
    stack *operator_stack = NULL;
    stack *curr;
    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            curr = (stack*)malloc(sizeof(stack));
            curr->value = ch - '0';
            curr->oper = 0;
            curr->next = output_stack;
            output_stack = curr;
        } else {
            break;
        }
    }
    curr = output_stack;
    while (curr) {
        printf("%i\n", curr->value);
        curr = curr->next;
    }

    return 0;
}