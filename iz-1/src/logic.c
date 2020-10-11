#include "logic.h"

float length(Coord o1, Coord o2) {
    return (float)sqrt(pow((o1.x - o2.x), 2) + pow((o1.y - o2.y), 2));
}

float area_triangle(const Coord o1, const Coord o2, const Coord o3) {
    float a = length(o1, o2);
    float b = length(o2, o3);
    float c = length(o1, o3);
    float p = (a + b + c) / 2;
    float sum = sqrt(p * (p - a) * (p - b) * (p - c));
    return sum;
}

float *area_figure(float **x, size_t size_x, float **y, size_t size_y) {
    if (size_x < 3 || size_y < 3)
        return NULL;

    if (size_x != size_y)
        return NULL;

    float *area = (float*) malloc(sizeof(float));
    *area = 0;

    const Coord start = {*(x[0]), *(y[0])};
    Coord first = {*(x[1]), *(y[1])};

    for (int i = 2; i < size_x; i++) {
        Coord second = first;
        first.x = *(x[i]);
        first.y = *(y[i]);

        (*area) += area_triangle(start, first, second);
    }

    return area;
}
