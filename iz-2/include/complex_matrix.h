
#ifndef IZ_2_COMPLEX_MATRIX_H
#define IZ_2_COMPLEX_MATRIX_H

#include "stdio.h"
#include <stdio.h>
#include <string.h>
#include "matrix_memory.h"
#include <pthread.h>

int matrix_reflection(int** arr, const int* row, const int* col, int** arr_tr);
int matrix_reflection_stream(FILE* input, FILE* output);
int matrix_reflection_file(const char * file_name_input, const char * file_name_output);

#endif //IZ_2_COMPLEX_MATRIX_H
