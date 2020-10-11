#include "cl_console.h"

int get_points(float **x, float **y, const int max){
    int num = max + 1;
    while (num > max) {
        printf("Input number point, less %d\n", max);
        scanf("%d", &num);
    }

    for(int i = 0; i < num; i++){
        printf("Input x%d y%d\n", i+1, i+1);
        scanf("%f%f", x[i], y[i]);
    }

    return num;
}

void set_result(const float *res){
    printf("Area = %f\n", *res);
}
