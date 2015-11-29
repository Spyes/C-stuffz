#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "stack.h"

int isoper(int c);
int convert_to_rpn(s **input, s **output, s **output_tail);

#endif  // SHUNTING_YARD_H
