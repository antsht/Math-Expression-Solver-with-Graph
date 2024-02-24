#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
List of operations:
+ = +
- = - binary
~ = - unary
* = *
/ = /
( = (
) = )
s = sin(x)
c = cos(x)
t = tan(x)
g = ctg(x)
q = sqrt(x)
l = ln(x)
v = if value is stored

*/

token *tokenize_string(char *expr, double x, int *tokens_cnt) {
    int max_len = strlen(expr);
    token *tokens = (token *)calloc(max_len, sizeof(token));
    int curr_token = 0;
    while (tokens && *expr) {
        int is_space = 0;
        if (*expr == ' ' || *expr == 10) {
            is_space = 1;
        } else if (*expr == '-' && curr_token == 0) {
            tokens[curr_token].operation = '~';
        } else if (*expr == '-' && curr_token > 0 && tokens[curr_token - 1].operation != 'v' &&
                   tokens[curr_token - 1].operation != ')') {
            tokens[curr_token].operation = '~';
        } else if ((*expr == '-' && curr_token > 0 && tokens[curr_token - 1].operation == 'v') ||
                   (*expr == '-' && curr_token > 0 && tokens[curr_token - 1].operation == ')')) {
            tokens[curr_token].operation = '-';
        } else if ((*expr == '+' && curr_token > 0 && tokens[curr_token - 1].operation == 'v') ||
                   (*expr == '+' && curr_token > 0 && tokens[curr_token - 1].operation == ')')) {
            tokens[curr_token].operation = '+';
        } else if ((*expr == '*' && curr_token > 0 && tokens[curr_token - 1].operation == 'v') ||
                   (*expr == '*' && curr_token > 0 && tokens[curr_token - 1].operation == ')')) {
            tokens[curr_token].operation = '*';
        } else if ((*expr == '/' && curr_token > 0 && tokens[curr_token - 1].operation == 'v') ||
                   (*expr == '/' && curr_token > 0 && tokens[curr_token - 1].operation == ')')) {
            tokens[curr_token].operation = '/';
        } else if (*expr == '(') {
            tokens[curr_token].operation = '(';
        } else if (*expr == ')' && curr_token > 0) {
            tokens[curr_token].operation = ')';
        } else if (*expr == 's' && *(expr + 1) == 'i' && *(expr + 2) == 'n') {
            write_token_and_go_on(tokens, curr_token, 's', 2, &expr);
        } else if (*expr == 's' && *(expr + 1) == 'q' && *(expr + 2) == 'r' && *(expr + 3) == 't') {
            write_token_and_go_on(tokens, curr_token, 'q', 3, &expr);
        } else if (*expr == 'c' && *(expr + 1) == 'o' && *(expr + 2) == 's') {
            write_token_and_go_on(tokens, curr_token, 'c', 2, &expr);
        } else if (*expr == 't' && *(expr + 1) == 'a' && *(expr + 2) == 'n') {
            write_token_and_go_on(tokens, curr_token, 't', 2, &expr);
        } else if (*expr == 'l' && *(expr + 1) == 'n') {
            write_token_and_go_on(tokens, curr_token, 'l', 1, &expr);
        } else if (*expr == 'c' && *(expr + 1) == 't' && *(expr + 2) == 'g') {
            write_token_and_go_on(tokens, curr_token, 'g', 2, &expr);
        } else if (*expr == 'x' && *(expr + 1) != 'x') {
            tokens[curr_token].operation = 'v';
            tokens[curr_token].value = x;
        } else if ('0' <= (*expr) && (*expr) <= '9') {
            char *stopstring;
            tokens[curr_token].operation = 'v';
            tokens[curr_token].value = strtof(expr, &stopstring);
            expr = stopstring - 1;
        } else {
            quit(tokens);
        }
        expr++;
        if (!is_space) curr_token++;
    }
    *tokens_cnt = curr_token - 1;
    return tokens;
}

void write_token_and_go_on(token *tokens, int token_index, char operation, int offset, char **expr) {
    tokens[token_index].operation = operation;
    *expr += offset;
}

void quit(token *tokens) {
    free(tokens);
    printf("Incorrect input... DOORS will be closed forever!\n");
    exit(EXIT_FAILURE);
}