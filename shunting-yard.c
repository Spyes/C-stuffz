#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

// Input states
#define DIGIT 1
#define OPER 2

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
    //printf("%c > %c = %i\n", oper1, oper2, oper_precedence(oper1) > oper_precedence(oper2));
    // error check (oper_precedence returns -1 on err)
    return (oper_precedence(oper1) > oper_precedence(oper2));
}

int equal_precedence(int oper1, int oper2)
{
    //printf("%c == %c = %i\n", oper1, oper2, oper_precedence(oper1) == oper_precedence(oper2));
    return (oper_precedence(oper1) == oper_precedence(oper2));
}

int parse_input(char *input_string, s **input, s **input_tail)
{
    s *input_int,
	*input_op;
    int num_set = 0;
    int cur_n = 0;
    int count = 0;
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
                count++;
	    }
	    cur_n = 0;
	    num_set = 0;
	    input_op = create_node(ch, 1);
	    append(input, input_tail, &input_op);
            count++;
	} else if (isblank(ch))
	    ;
	else
	    return -1;
    }
    // because the exit-cond is ch != '\0', we miss out on pushing the last number
    // in the equation...
    if (cur_n) {
        input_int = create_node(cur_n, 0);
        append(input, input_tail, &input_int);
        count++;
    }
    return count;
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
	    if (curr->val == ')') {
		curr_op = operators;
		if (!curr_op)
		    return -1;
		while(curr_op->val != '(') {
		    o = pop(&operators);
		    append(output, output_tail, &o);
                    print_stacks((*output), operators);
		    curr_op = operators;
		    if (!curr_op)  // mismatching parans
			return -1;
		}
		pop(&operators);
		continue;
	    } else {
		curr_op = operators;
		while (curr_op && curr_op->val != '(' &&
		       (takes_precedence(curr->val, curr_op->val) ||
			equal_precedence(curr->val, curr_op->val))) {
		    o = pop(&operators);
		    append(output, output_tail, &o);
                    print_stacks((*output), operators);
		    curr_op = operators;
		}
	    }
            push(&operators, &curr);
            print_stacks((*output), operators);
        } else {
	    append(output, output_tail, &curr);
            print_stacks((*output), operators);
        }
    }

    while (operators != NULL) {
	if (operators->val == '(' || operators->val == ')') // mismatching parans
	    return -1;
        o = pop(&operators);
        append(output, output_tail, &o);
        print_stacks((*output), operators);
    }    
}

int main(int argc, char **argv)
{
    s *input = NULL,
	*input_tail = NULL;
    s *output = NULL,
        *output_tail = NULL,
        *operators = NULL;

    char input_string[30];
    printf("Input an equation: \n\t");
    scanf("%30[^\n]", input_string);

    parse_input(input_string, &input, &input_tail);
    convert_to_rpn(input, &output, &output_tail);
    /*
    while (output != NULL) {
        if (output->oper)
            printf("%c\n", output->val);
        else
            printf("%i\n", output->val);
        output = output->next;
    }
    */
    return 0;
}
