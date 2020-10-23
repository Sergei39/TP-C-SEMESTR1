
#ifndef IZ_2_MATRIX_H
#define IZ_2_MATRIX_H

#include <stdio.h>
#include "malloc.h"
#include "matrix_member.h"


int** matrix_read_file(const char* file_name, int* row, int* col);
void matrix_reflection_and_write(FILE* stream, int** arr, const int* row, const int* col);
int** matrix_read(FILE* stream, int* row, int* col);

#endif //IZ_2_MATRIX_H
