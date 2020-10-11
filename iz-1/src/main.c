#include "logic.h"
#include "cl_console.h"

#define MAX_POINT 100

int main() {
    float *x[MAX_POINT], *y[MAX_POINT];
    for(int i = 0; i < MAX_POINT; i++){
        x[i] = (float*) malloc(sizeof(float));
        y[i] = (float*) malloc(sizeof(float));
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
