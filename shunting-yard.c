#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

// Input states
#define DIGIT 1
#define OPER 2

int oper_precedence(int oper)
{
    if (oper == '^')
	return 4;
    else if (oper == '*' || oper == '/')
	return 3;
    else if (oper == '+' || oper == '-')
	return 2;
    return -1;
}

int isoper(int c)
{
    return (c == '^' ||
	    c == '+' || c == '-' ||
            c == '/' || c == '*' ||
	    c == '(' || c == ')');
}

// Does oper1 take precedence over oper2?
int takes_precedence(int oper1, int oper2)
{
    // error check (oper_precedence returns -1 on err)
    return (oper_precedence(oper1) > oper_precedence(oper2));
}

int equal_precedence(int oper1, int oper2)
{
    return (oper_precedence(oper1) == oper_precedence(oper2));
}

void parse_input(char *input_string, s **input, s **input_tail)
{
    s *input_int,
	*input_op;
    int input_state = DIGIT;
    int num_set = 0;
    int cur_n = 0;

    int ch;
    int i;
    for (i = 0, ch = input_string[i]; ch != '\0'; i++, ch = input_string[i]) {
	if (isdigit(ch)) {
	    num_set = 1;
	    cur_n *= 10;
	    cur_n += ch - '0';
	} else if (ispunct(ch)) {
	    if (!isoper(ch)) return;
	    if (num_set) {
		input_int = create_node(cur_n, 0);
		append(input, input_tail, &input_int);
	    }
	    cur_n = 0;
	    num_set = 0;
	    input_op = create_node(ch, 1);
	    append(input, input_tail, &input_op);
	} else if (isblank(ch))
	    ;
	else
	    return NULL;
    }
    // because the exist-cond is ch != '\0', we miss out on pushing the last number
    // in the equation...
    input_int = create_node(cur_n, 0);
    append(input, input_tail, &input_int);
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

    char input_string[30];
    printf("Input an equation: \n\t");
    scanf("%30[^\n]", input_string);

    parse_input(input_string, &input, &input_tail);
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
        } else
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
