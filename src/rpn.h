#ifndef RPN_H
#define RPN_H

#include "data_lib.h"

int precedence(char op);
void calculateRPN(char *expression, NumStack *s);
void parseToRPN(char *infix, char *postfix);
double evaluate_expression(char *expression, double x);
void exit_with_error(char *msg);

#endif