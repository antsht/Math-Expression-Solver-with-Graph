#include "graph.h"

#include <stdio.h>

#include "data_lib.h"
#include "draw.h"
#include "rpn.h"
#include "tokenizer.h"

int main(void) {
    char expr[MAX_EXPR_SIZE];
    fgets(expr, MAX_EXPR_SIZE - 2, stdin);

    Point points[COLS];
    fill_points_coords(points, expr);
    output_function(points);

    return 0;
}