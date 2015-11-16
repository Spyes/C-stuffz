#include "stack.h"
#include "shunting-yard.h"
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

// rpn = reverse polish notation
int convert_to_rpn(s *input, s **output, s **output_tail)
{
    s *operators = NULL,
        *curr,
        *o2;
    while (input) {
	curr = pop(&input);
        if (curr->oper) {
	    switch (curr->oper) {
	    case ')':
            case ',':
		o2 = operators;
		if (!o2)
		    return -1;
		while(o2->oper && o2->oper != '(') {
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		    if (!o2)  // mismatching parans
			return -1;
		}
		if (operators->oper == '(')
		    pop(&operators);
		break;
	    case '*':
	    case '/':
	    case '+':
	    case '-':
	    case '^':
		o2 = operators;
		while (o2 && o2->oper != '(' &&
		       operators_precedence_check(curr, o2)) {
		    append_operators_to_output_queue(&operators, output, output_tail, &o2);
		    if (o2) o2 = o2->next;
		}
		push(&operators, &curr);
		break;
	    case '(':
		push(&operators, &curr);
		break;
	    default:
		return -1;
		break;
	    }
        } else if (curr->func)
            push(&operators, &curr);
        else
	    append(output, output_tail, &curr);
    }

    while (operators != NULL) {
	if (operators->oper == '(' || operators->oper == ')') // mismatching parans
	    return -1;
	append_operators_to_output_queue(&operators, output, output_tail, NULL);
    }    
}
