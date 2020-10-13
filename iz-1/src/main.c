#include "logic.h"
#include "cl_console.h"
#include <stdio.h>

#define MAX_POINT 100

int main() {
    float *x[MAX_POINT], *y[MAX_POINT];

    for(int i = 0; i < MAX_POINT; i++){
        x[i] = (float*) malloc(sizeof(float));
        y[i] = (float*) malloc(sizeof(float));

        if (x[i] == NULL || y[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(x[j]);
                free(y[j]);
            }
            if (x[i] == NULL)
                free(x[i]);
            if (y[i] == NULL)
                free(y[i]);

            return 0;
        }
    }

    int num = get_points(x, y, MAX_POINT);

    float *res = area_figure(x, y, num);
    set_result(res);

    free(res);

    for(int i = 0; i < MAX_POINT; i++) {
        free(x[i]);
        free(y[i]);
    }

    return 0;
}
