#ifndef TOKENIZER_H
#define TOKENIZER_H

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

typedef struct s_token {
    char operation;
    double value;
} token;

token *tokenize_string(char *str_to_parse, double x, int *tokens_cnt);
void write_token_and_go_on(token *tokens, int token_index, char operation, int offset, char **expr);
void quit(token *tokens);

#endif