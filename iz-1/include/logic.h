//
// Created by sergei on 09.10.2020.
//

#ifndef IZ_1_LOGIC_H
#define IZ_1_LOGIC_H

//#include <math.h>
#include <stdlib.h>
#include "my_math.h"

typedef struct {
    float x;
    float y;
} Coord;

float *area_figure(float **const x, float **const y, const size_t size_arr);


#endif //IZ_1_LOGIC_H
