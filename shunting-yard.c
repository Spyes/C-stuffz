#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

// Input states
#define DIGIT 1
#define OPER 2
#define PARAN 3

int isoper(int c)
{
    return (c == '+' || c == '-' ||
            c == '/' || c == '*' ||
	    c == '(' || c == ')');
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
    s *input = NULL,
	*input_tail = NULL;
    s *output = NULL,
        *output_tail = NULL,
        *operators = NULL;
    s *curr,
	*curr_op,
        *n,
        *o;
    s *input_int,
	*input_op;

    int input_state = DIGIT;
    int num_set = 0;
    int cur_n = 0;

    int done = 0;
    int ch;
    char input_string[30];
    printf("Input an equation: \n\t");
    scanf("%30[^\n]", &input_string);

    int i;
    for (i = 0, ch = input_string[i]; ch != '\0'; i++, ch = input_string[i]) {
        if (input_state == DIGIT) {
            if (!isdigit(ch)) {
                if (ch == '(' || ch == ')')
                    ;
                else if (isblank(ch) && num_set) {
		    input_int = create_node(cur_n, 0);
		    append(&input, &input_tail, &input_int);
                    input_state = OPER;
                }
                continue;
            }

            num_set = 1;
            if(num_set)
                cur_n *= 10;
            cur_n += ch - '0';
        } else if (input_state == OPER) {
            num_set = 0;
            cur_n = 0;

            if (!ispunct(ch))
                continue;
        //    else if (ch != '+' || ch != '-' || ch != '*' || ch != '/')
         //       continue;

	    input_op = create_node(ch, 1);
	    append(&input, &input_tail, &input_op);
            input_state = DIGIT;
        }
    }
    // because the exist-cond is ch != '\0', we miss out on pushing the last number
    // in the equation...
    input_int = create_node(cur_n, 0);
    append(&input, &input_tail, &input_int);

    while (input) {
	curr = pop(&input);
        if (curr->oper) {
	    if (curr->val == ')') {
		curr_op = operators;
		if (!curr_op)
		    return 1;
		while(curr_op->val != '(') {
		    o = pop(&operators);
		    append(&output, &output_tail, &o);
		    curr_op = operators;
		    if (!curr_op)  // mismatching parans
			return 1;
		}
		pop(&operators);
		continue;
	    } else {
		curr_op = operators;
		while (curr_op &&
		       (takes_precedence(curr_op->val, curr->val) ||
			equal_precedence(curr_op->val, curr->val))) {
		    o = pop(&operators);
		    append(&output, &output_tail, &o);
		    curr_op = operators;
		}
	    }
            push(&operators, &curr);
        }
        else
	    append(&output, &output_tail, &curr);
    }

    while (operators != NULL) {
	if (operators->val == '(' || operators->val == ')') // mismatching parans
	    return 1;
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
