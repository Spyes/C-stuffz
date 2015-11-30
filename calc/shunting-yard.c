#include "stack.h"
#include "shunting-yard.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Associativity
#define ASSOC_LEFT  10
#define ASSOC_RIGHT 11

int isoper(int c)
{
    return (c == ',' || c == '^' ||
	    c == '+' || c == '-' ||
            c == '/' || c == '*' ||
	    c == '(' || c == ')');
}

int oper_precedence(int oper)
{
    if (oper == '^')
	return 4;
    else if (oper == '*' || oper == '/')
	return 3;
    else if (oper == '+' || oper == '-')
	return 2;
    return 0;
}

int oper_associativity(int oper)
{
    if (!isoper(oper))
        return -1;
    if (oper == '^')
        return ASSOC_RIGHT;
    return ASSOC_LEFT;
}

int less_than_or_equal_precedence(int oper1, int oper2)
{
    return oper_precedence(oper1) <= oper_precedence(oper2);
}

// oper1 precedence < oper2 precedence
int less_than_precedence(int oper1, int oper2)
{
    return oper_precedence(oper1) < oper_precedence(oper2);
}

void append_operators_to_output_queue(s **operators, s **output, s **output_tail, s **o2)
{
    s *o = pop(operators);
    append(output, output_tail, &o);
    if (o2)
	(*o2) = (*operators);
}

int operators_precedence_check(s *oper1, s *oper2)
{
    return ((oper_associativity(oper1->oper) == ASSOC_LEFT &&
	    less_than_or_equal_precedence(oper1->oper, oper2->oper)) ||
	(oper_associativity(oper1->oper) == ASSOC_RIGHT &&
	 less_than_precedence(oper1->oper, oper2->oper)));
}

int convert_to_rpn(s **input, s **output, s **output_tail)
{
    s *operators = NULL,
	*curr,
	*temp,
	*o2;

    while ((*input)) {
	curr = pop(input);
	if (curr->val) {
	    // if the token is a number then add it to the output queue
	    append(output, output_tail, &curr);
	} else if (curr->func) {
	    // if the token is a function then push it onto the stack
	    push(&operators, &curr);
	} else if (curr->oper) {
	    if (curr->oper == '(')
		push(&operators, &curr);
	    else if (curr->oper == ')') {
		o2 = operators;
		while (o2 && o2->oper != '(')
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		if (o2 && o2->oper == '(') {
		    temp = pop(&operators);
		    free(temp);
		    o2 = operators;
		}
		if (o2 && o2->func)
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		else
		    ; // ERROR
	    } else if (curr->oper == ',') {
		// if the token is a function separator
		o2 = operators;
		while (o2 && o2->oper != '(')
		    // until the token at the top of the stack is left parenthesis
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		    // pop operators off the stack onto the output queue
		    // TODO handle mismatching parens or misplaced comma
	    } else {
		// if the token is an operator o1
		o2 = operators;
		while (o2 && o2->oper != '(' && operators_precedence_check(curr, o2))
		    // while there is a token o2 on the top of the stack and either
		    // o1 is left-associative and its precedence is less than or equal to o2 OR
		    // o1 is right-associative and its precedence is less than o2
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		    // pop o2 off the stack onto the output queue
		// push o1 onto the operators stack
		push(&operators, &curr);
	    }
	}
    }

    while (operators != NULL) {
	if (operators->oper == '(' || operators->oper == ')') // mismatching parans
	    error("Mismatching parens");
	append_operators_to_output_queue(&operators, output, output_tail, NULL);
    }
}
