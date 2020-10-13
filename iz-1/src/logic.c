#include "logic.h"


float length(const Coord o1, const Coord o2) {
    return (float)my_sqrt(my_pow((o1.x - o2.x), 2) + my_pow((o1.y - o2.y), 2));
}

float area_triangle(const Coord o1, const Coord o2, const Coord o3) {
    float a = length(o1, o2);
    float b = length(o2, o3);
    float c = length(o1, o3);
    float p = (a + b + c) / 2;
    float sum = my_sqrt(p * (p - a) * (p - b) * (p - c));
    return sum;
}

float *area_figure(float **const x, float **const y, const size_t size_arr) {

    if (x == NULL || y == NULL)
        return NULL;

    for (int i = 0; i < size_arr; i++) {
        if (x[i] == 0 || y[i] == NULL)
            return NULL;
    }

    if (size_arr < 3)
        return NULL;

    float *area = (float*) malloc(sizeof(float));
    *area = 0;

    const Coord start = {*(x[0]), *(y[0])};
    Coord first = {*(x[1]), *(y[1])};

    for (int i = 2; i < size_arr; i++) {
        if (x[i] == NULL || y[i] == NULL) {
            free(area);
            return NULL;
        }

        Coord second = first;

        first.x = *(x[i]);
        first.y = *(y[i]);

        (*area) += area_triangle(start, first, second);
    }

    return area;
}
