#ifndef DATA_LIB_H
#define DATA_LIB_H

#include "graph.h"
#define is_digit(c) ((c >= '0' && c <= '9') || (c == 'x'))

typedef struct {
    double x;
    double y;
    double y_norm;
    int is_nan;
} Point;
typedef struct {
    int top;
    double stack[MAX_STACK_SIZE];
} NumStack;

typedef struct {
    int top;
    char stack[MAX_STACK_SIZE];
} OpStack;

void initNumStack(NumStack *s);
void initOpStack(OpStack *s);
int isNumStackEmpty(NumStack *s);
int isOpStackEmpty(OpStack *s);
int isNumStackFull(NumStack *s);
int isOpStackFull(OpStack *s);
void pushNum(NumStack *s, double value);
void pushOp(OpStack *s, char op);
double popNum(NumStack *s);
char popOp(OpStack *s);
void f_add(NumStack *s);
void f_subtract(NumStack *s);
void f_multiply(NumStack *s);
void f_divide(NumStack *s);
void f_negate(NumStack *s);
void f_sin(NumStack *s);
void f_cos(NumStack *s);
void f_tg(NumStack *s);
void f_ctg(NumStack *s);
void f_ln(NumStack *s);
void f_sqrt(NumStack *s);
void normalize_and_scale(Point *points);
void fill_points_coords(Point *points, char *expr);

#endif