#include "draw.h"

#include <stdio.h>

#include "data_lib.h"
#include "graph.h"

void output_function(Point *points) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if ((points[j].is_nan == 0) && (int)(points[j].y_norm + Y_OFFSET) == i)
                printf("%c", POINT_CHAR);
            else
                printf("%c", VOID_CHAR);
        }
        printf("\n");
    }
}