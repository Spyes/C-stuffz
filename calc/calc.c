#include <stdio.h>
#include <ctype.h>

// Input states
#define DIGIT 1
#define OPER  2
#define PARAN 3

// Calculation states
#define ADD 10
#define SUB 11
#define MUL 12
#define DIV 13

int do_calculation(int *calc)
{
    int num1 = calc[0];
    int num2 = calc[2];
    int op   = calc[1];
    int r;
    
    switch (op) {
    case ADD:
        r = num1 + num2;
        break;
    default:
        break;
    }
    printf("%i\n", r);
    return r;
}

int main(int argc, char **argv)
{
    int ch;
    int input_state = DIGIT;
    int calc_state = NULL;
    int cur_n = 0;
    int num_set = 0;
    int i = 0;
    int parans = 0;
    int result = 0;
    
    while ((ch = getchar()) != EOF) {
        if (ch == '\n')
            ;//do_calculation();
        if (input_state == DIGIT) {
            if (!isdigit(ch)) {
                if (ch == '(')
                    parans++;
                else if (ch == ')') {
                    parans--;
                    if (parans == 0)
                        ;// do calculation
                } else if (isblank(ch) && num_set) {
                    input_state = OPER;
                }
                continue;
            }
            num_set = 1;
            ch = ch - '0';
            if (i > 0)
                cur_n *= 10;
            cur_n += ch;
            printf("%i\n", cur_n);
            i++;
        } else if (input_state == OPER) {
            i = 0;
            num_set = 0;
            cur_n = 0;
            if (!ispunct(ch))
                continue;
            switch (ch) {
            case '+':
                calc_state = ADD;
                break;
            case '-':
                calc_state = SUB;
                break;
            case '*':
                calc_state = MUL;
                break;
            case '/':
                calc_state = DIV;
                break;
            }
            current_calc[1] = calc_state;
            input_state = DIGIT;
        }
    }
    
    printf("Result: %i\n", result);
    return 0;
}
