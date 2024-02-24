#include "data_lib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "rpn.h"
#include "tokenizer.h"

void initNumStack(NumStack *s) {
    s->top = -1;
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        s->stack[i] = 0;
    }
}

void initOpStack(OpStack *s) {
    s->top = -1;
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        s->stack[i] = 0;
    }
}

int isNumStackEmpty(NumStack *s) { return s->top == -1; }

int isOpStackEmpty(OpStack *s) { return s->top == -1; }

int isNumStackFull(NumStack *s) { return s->top == MAX_STACK_SIZE - 1; }

int isOpStackFull(OpStack *s) { return s->top == MAX_STACK_SIZE - 1; }

void pushNum(NumStack *s, double value) {
    if (!isNumStackFull(s)) {
        s->stack[++s->top] = value;
    } else {
        printf("Number Stack is full\n");
    }
}

void pushOp(OpStack *s, char op) {
    if (!isOpStackFull(s)) {
        s->stack[++s->top] = op;
    } else {
        printf("Operator Stack is full\n");
    }
}

double popNum(NumStack *s) {
    if (!isNumStackEmpty(s)) {
        return s->stack[s->top--];
    } else {
#ifdef DEBUG
        printf("Number Stack is empty\n");
#endif
        return -1;  //  error code
    }
}

char popOp(OpStack *s) {
    if (!isOpStackEmpty(s)) {
        return s->stack[s->top--];
    } else {
#ifdef DEBUG
        printf("Operator Stack is empty\n");
#endif
        return '\0';  //  error code
    }
}

void f_add(NumStack *s) {
    double b = popNum(s);
    double a = popNum(s);
    pushNum(s, a + b);
}

void f_subtract(NumStack *s) {
    double b = popNum(s);
    double a = popNum(s);
    pushNum(s, a - b);
}

void f_multiply(NumStack *s) {
    double b = popNum(s);
    double a = popNum(s);
    pushNum(s, a * b);
}

void f_divide(NumStack *s) {
    double b = popNum(s);
    double a = popNum(s);
    if (b != 0) {
        pushNum(s, a / b);
    } else {
        pushNum(s, NAN);
    }
}

void f_negate(NumStack *s) {
    double a = popNum(s);
    pushNum(s, -a);
}

void f_sin(NumStack *s) {
    double a = popNum(s);
    pushNum(s, sin(a));
}

void f_cos(NumStack *s) {
    double a = popNum(s);
    pushNum(s, cos(a));
}

void f_tg(NumStack *s) {
    double a = popNum(s);
    pushNum(s, tan(a));
}

void f_ctg(NumStack *s) {
    double a = popNum(s);
    pushNum(s, 1 / tan(a));
}

void f_ln(NumStack *s) {
    double a = popNum(s);
    pushNum(s, log(a));
}

void f_sqrt(NumStack *s) {
    double a = popNum(s);
    pushNum(s, sqrt(a));
}

void normalize_and_scale(Point *points) {
    double max = 0;
    for (int i = 0; i < COLS; i++) {
        if (points[i].y > max && points[i].is_nan == 0)
            max = points[i].y;

        else if ((-points[i].y) > max && points[i].is_nan == 0)
            max = -points[i].y;
    }
    for (int i = 0; i < COLS; i++) {
        if (max != 0)
            points[i].y_norm = (int)round(points[i].y / max * Y_SCALE);
        else
            points[i].y_norm = 0;
    }
}
void fill_points_coords(Point *points, char *expr) {
    double step = X_RANGE_FACTOR * PI / (COLS - 1);

    for (int i = 0; i < COLS; i++) {
        points[i].x = i * step;

        points[i].y = evaluate_expression(expr, points[i].x);
        points[i].is_nan =
            (!(points[i].y == points[i].y) || points[i].y == INFINITY || points[i].y == -INFINITY) ? 1 : 0;
        points[i].y_norm = 0;
    }
    normalize_and_scale(points);
#ifdef DEBUG
    for (int i = 0; i < COLS; i++) {
        printf("P%02d x=%lf y= %lf y_NORM= %lf Is_NAN: %1d\n", i + 1, points[i].x, points[i].y,
               points[i].y_norm, points[i].is_nan);
    }
#endif
}
