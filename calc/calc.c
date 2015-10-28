#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Input states
#define DIGIT 1
#define OPER 2
#define PARAN 3

// Calculation states
#define ADD 10
#define SUB 11
#define MUL 12
#define DIV 13

struct tree_el {
    int val;
    int operator; // boolean
    struct tree_el* left, *right;
};

typedef struct tree_el node;

// example tree of 5 + (7 - 2)
//    +
//  5   -
//    7   2
void insert(node** tree, node* item)
{
    if (!(*tree)) {
        (*tree) = item;
        return;
    }

    insert(&(*tree)->left, item);
}

int main(int argc, char** argv)
{
    int ch;
    int input_state = DIGIT;
    int cur_n = 0;
    int num_set = 0; // this will allow us to forget about leading whitespaces
    int parans = 0;
    int result = 0;
    node* curr_int, *curr_op, *root;
    root = NULL;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n')
            ; // do_calculation

        if (input_state == DIGIT) {
            if (!isdigit(ch)) {
                if (ch == '(' || ch == ')')
                    ;
                else if (isblank(ch) && num_set) {
                    curr_int = (node*)malloc(sizeof(node));
                    curr_int->operator= 0;
                    curr_int->val = cur_n;
                    input_state = OPER;
                }
                continue;
            }

            num_set = 1;
            ch = ch - '0';
            if(num_set)
                cur_n *= 10;
            cur_n += ch;
            printf("%i\n", cur_n);
        } else if (input_state == OPER) {
            num_set = 0;
            cur_n = 0;

            if (!ispunct(ch))
                continue;
        //    else if (ch != '+' || ch != '-' || ch != '*' || ch != '/')
         //       continue;

            curr_op = (node*)malloc(sizeof(node));
            curr_op->operator= 1;
            curr_op->val = ch;
            insert(&root, curr_op);
            insert(&root, curr_int);
            input_state = DIGIT;
        }
    }

    printf("Result: %i\n", result);
    return 0;
}
