#include "shunting-yard.h"
#include "reverse-polish.h"
#include "stack.h"
#include <stdio.h>
#include <ctype.h>

int parse_input(char *input_string, s **input, s **input_tail)
{
    s *input_int,
	*input_op,
	*input_func;
    int num_set = 0;
    int cur_n = 0;
    int count = 0;
    char cur_func[25] = "";
    int ch;
    int i;
    for (i = 0, ch = input_string[i]; ch != '\0'; i++, ch = input_string[i]) {
	if (isdigit(ch)) {
	    num_set = 1;
	    cur_n *= 10;
	    cur_n += ch - '0';
	} else if (ispunct(ch)) {
	    if (!isoper(ch)) return -1;
            if (ch == '(' && cur_func) {
		input_func = create_node(0, 0, cur_func);
		append(input, input_tail, &input_func);
		count++;
                sprintf(cur_func, "");
	    } else if (num_set) {
		input_int = create_node(cur_n, 0, NULL);
		append(input, input_tail, &input_int);
                count++;
	    }
	    cur_n = 0;
	    num_set = 0;
	    sprintf(cur_func, "");
	    input_op = create_node(ch, 1, NULL);
	    append(input, input_tail, &input_op);
            count++;
	} else if (isalpha(ch))
	    sprintf(cur_func, "%s%c", cur_func, ch);
	else if (isblank(ch))
            ;
	else
	    return -1;
    }
    // because the exit-cond is ch != '\0', we miss out on pushing the last number
    // in the equation...
    if (cur_n) {
        input_int = create_node(cur_n, 0, NULL);
        append(input, input_tail, &input_int);
        count++;
    }
    return count;
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

    if (parse_input(input_string, &input, &input_tail) == -1)
	return 1;  // ERROR
    convert_to_rpn(input, &output, &output_tail);
    float result = reverse_polish_calculation(&output);
    printf("Result: %f\n", result);

    return 0;
}
