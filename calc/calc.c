#include "shunting-yard.h"
#include "reverse-polish.h"
#include "stack.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_func_token(char *cur_func, s **input, s **input_tail, int *count)
{
    s *input_func = create_stack_node(0, 0, cur_func);
    append(input, input_tail, &input_func);
    (*count)++;
    sprintf(cur_func, "");
}

void add_oper_token(int ch, s **input, s **input_tail, int *count, char *cur_func, int *cur_n, int *num_set)
{
    (*cur_n) = 0;
    (*num_set) = 0;
    sprintf(cur_func, "");
    s *input_op = create_stack_node(ch, 1, NULL);
    append(input, input_tail, &input_op);
    (*count)++;
}

void add_int_token(int cur_n, s **input, s **input_tail, int *count, int *negative)
{
    s *input_int = create_stack_node(cur_n, 0, NULL);
    append(input, input_tail, &input_int);
    (*count)++;
    if (negative)
	(*negative) = 0;    
}

int parse_input(char *input_string, s **input, s **input_tail)
{
    int num_set = 0, cur_n = 0, count = 0, negative = 0;
    char cur_func[25] = "";
    int ch, i;
    for (i = 0, ch = input_string[i]; ch != '\0'; i++, ch = input_string[i]) {
	if (isdigit(ch)) {
	    num_set = 1;
	    cur_n *= 10;
	    cur_n += ch - '0';
	    if (negative) cur_n *= -1;
	} else if (ispunct(ch)) {
	    if (!isoper(ch)) return -1;
            if (ch == '(' && (strcmp(cur_func, "") != 0))
		add_func_token(cur_func, input, input_tail, &count);
	    else if (num_set) {
		add_int_token(cur_n, input, input_tail, &count, &negative);
	    } else if (ch == '-') {
		if (!(*input_tail) || (*input_tail)->oper) {
		    negative = 1;
		    continue;
		} else
		    negative = 0;
	    }
	    add_oper_token(ch, input, input_tail, &count, cur_func, &cur_n, &num_set);
	} else if (isalpha(ch))
	    sprintf(cur_func, "%s%c", cur_func, ch);
	else if (isblank(ch))
	    ;
	else
	    return -1;
    }
    // because the exit-cond is ch != '\0', we miss out on pushing the last number
    // in the equation...
    if (cur_n)
	add_int_token(cur_n, input, input_tail, &count, NULL);
    return count;
}

void set_functions(s **hash_table)
{
    int j;
    for (j = 0; j < HASH_SIZE; j++)
	hash_table[j] = NULL;

    s *n = create_hash_node("max", 2);
    insert(hash_table, &n);
    n = create_hash_node("exp", 1);
    insert(hash_table, &n);
}

int main(int argc, char **argv)
{
    s *input = NULL,
	*input_tail = NULL;
    s *output = NULL,
        *output_tail = NULL;
    s *functions[HASH_SIZE];

    int i;
    for (i = 0; i < HASH_SIZE; i++)
	functions[i] = NULL;

    
    set_functions(functions);

    char input_string[30];
    printf("Input an equation: \n\t");
    scanf("%30[^\n]", input_string);

    if (parse_input(input_string, &input, &input_tail) == -1)
	error("Can't parse input string");
    convert_to_rpn(&input, &output, &output_tail);
    float result = reverse_polish_calculation(&output, functions);
    printf("Result: %f\n", result);

    s *cur = NULL, *temp = NULL;
    cur = input;
    while (cur) {
	temp = cur->next;
	free(cur);
	cur = temp;
    }

    cur = output;
    temp = NULL;
    while (cur) {
	temp = cur->next;
	free(cur);
	cur = temp;
    }

    for (i = 0; i < HASH_SIZE; i++) {
	cur = functions[i];
	while (cur) {
	    temp = cur->next;
	    free(cur);
	    cur = temp;
	}
    }
    
    return 0;
}
