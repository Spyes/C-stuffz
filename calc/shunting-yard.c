#include "stack.h"
#include "shunting-yard.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Associativity
#define ASSOC_LEFT  10
#define ASSOC_RIGHT 11

int oper_precedence(int oper)
{
    if (oper == '^')
	return 3;
    else if (oper == '*' || oper == '/')
	return 2;
    else if (oper == '+' || oper == '-')
	return 1;
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

void print_stacks(s *out, s *opers)
{
    s *cur;
    char opers_str[10] = "";
    char out_str[10] = "";
    cur = out;
    while (cur) {
        if (ispunct(cur->val))
            sprintf(out_str, "%s%c ", out_str, cur->val);
        else
            sprintf(out_str, "%s%i ", out_str, cur->val);
        cur = cur->next;
    }
    cur = opers;
    while (cur) {
        sprintf(opers_str, "%s%c ", opers_str, cur->val);
        cur = cur->next;
    }
    if (out || opers)
        printf("%s\t%s\n", out_str, opers_str);
}

// rpn = reverse polish notation
int convert_to_rpn(s *input, s **output, s **output_tail)
{
    s *operators = NULL,
        *curr,
        *curr_op,
        *o;
    while (input) {
	curr = pop(&input);
        if (curr->oper) {
	    if (curr->oper == ')') {
		curr_op = operators;
		if (!curr_op)
		    return -1;
		while(curr_op->oper != '(') {
		    o = pop(&operators);
		    append(output, output_tail, &o);
		    curr_op = operators;
		    if (!curr_op)  // mismatching parans
			return -1;
		}
		pop(&operators);
		continue;
	    } else {
		curr_op = operators;
		while (curr_op && curr_op->oper != '(' &&
		       (takes_precedence(curr->oper, curr_op->oper) ||
			equal_precedence(curr->oper, curr_op->oper))) {
		    o = pop(&operators);
		    append(output, output_tail, &o);
		    curr_op = operators;
		}
	    }
            push(&operators, &curr);
        } else {
	    append(output, output_tail, &curr);
        }
    }

    while (operators != NULL) {
	if (operators->oper == '(' || operators->oper == ')') // mismatching parans
	    return -1;
        o = pop(&operators);
        append(output, output_tail, &o);
    }    
}
