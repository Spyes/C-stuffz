#include <stdio.h>

// Input states
#define DIGIT 1
#define OPER  2
#define PARAN 3

// Calculation states
#define ADD 10
#define SUB 11
#define MUL 12
#define DIV 13

int main(int argc, char **argv)
{
    int ch;
    int input_state = DIGIT;
    int calc_state = NULL;
    int cur_n = 0;
    int num_set = 0;
    int i = 0;
    int j = 0;
    while ((ch = getchar()) != EOF) {
        if (input_state == DIGIT) {
            if (!isdigit(ch)) {
                if (isblank(ch) && num_set)
                    input_state = OPER;
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
            printf("%i\n", calc_state);
            input_state = DIGIT;
        }
    }
    return 0;
}
