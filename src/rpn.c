#include "rpn.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_lib.h"
#include "tokenizer.h"

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'q':
        case 'l':
        case '~':
            return 3;
        default:
            return 0;
    }
}

void calculateRPN(char *expression, NumStack *s) {
    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (*token == '+')
            if (s->top > 0)
                f_add(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == '-')
            if (s->top > 0)
                f_subtract(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == '*')
            if (s->top > 0)
                f_multiply(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == '/')
            if (s->top > 0)
                f_divide(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == '~')
            if (s->top >= 0)
                f_negate(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 's')
            if (s->top >= 0)
                f_sin(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 'c')
            if (s->top >= 0)
                f_cos(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 't')
            if (s->top >= 0)
                f_tg(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 'g')
            if (s->top >= 0)
                f_ctg(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 'l')
            if (s->top >= 0)
                f_ln(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else if (*token == 'q')
            if (s->top >= 0)
                f_sqrt(s);
            else
                exit_with_error(EXIT_MESSAGE);
        else
            pushNum(s, atof(token));
        token = strtok(NULL, " ");
    }
}

void parseToRPN(char *infix, char *postfix) {
    OpStack s;
    initOpStack(&s);
    int post_pos = 0;
    for (int infix_pos = 0; infix[infix_pos]; infix_pos++) {
        if (is_digit(infix[infix_pos])) {
            while (is_digit(infix[infix_pos]) || infix[infix_pos] == '.') {
                postfix[post_pos++] = infix[infix_pos++];
            }
            postfix[post_pos++] = ' ';
            infix_pos--;
        } else if (infix[infix_pos] == '(') {
            pushOp(&s, '(');
        } else if (infix[infix_pos] == ')') {
            while (!isOpStackEmpty(&s) && s.stack[s.top] != '(') {
                postfix[post_pos++] = popOp(&s);
                postfix[post_pos++] = ' ';
            }
            popOp(&s);
        } else {
            while (!isOpStackEmpty(&s) && precedence(infix[infix_pos]) <= precedence(s.stack[s.top])) {
                postfix[post_pos++] = popOp(&s);
                postfix[post_pos++] = ' ';
            }
            pushOp(&s, infix[infix_pos]);
        }
    }
    while (!isOpStackEmpty(&s)) {
        postfix[post_pos++] = popOp(&s);
        postfix[post_pos++] = ' ';
    }
    postfix[post_pos] = '\0';
}

double evaluate_expression(char *expression, double x) {
    char infix[MAX_TOKENS] = {0};
    int tokens_cnt = 0;
    token *tokens = tokenize_string(expression, x, &tokens_cnt);
#ifdef DEBUG
    printf("Debug %d\n", tokens_cnt);
#endif
    for (int i = 0; i <= tokens_cnt; i++) {
        char buf[MAX_TOKENS];
        buf[i] = '\0';
        buf[i + 1] = '\0';
        if (tokens[i].operation == 'v') {
            sprintf(buf, "%.2lf", tokens[i].value);
        } else
            sprintf(buf, "%c", tokens[i].operation);
        strcat(infix, buf);
    }
    free(tokens);
#ifdef DEBUG
    printf("Debug: %s\n", infix);
#endif
    char postfix[MAX_EXPR_SIZE];
    parseToRPN(infix, postfix);
#ifdef DEBUG
    printf("RPN: %s\n", postfix);
#endif
    NumStack s;
    initNumStack(&s);

    calculateRPN(postfix, &s);

    if (s.top != 0) {
        exit_with_error(EXIT_MESSAGE);
    }
    double result = popNum(&s);
#ifdef DEBUG
    printf("Result: %f\n", result);
#endif
    return result;
}

void exit_with_error(char *msg) {
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}