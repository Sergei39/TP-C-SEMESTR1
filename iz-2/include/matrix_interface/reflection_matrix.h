
#ifndef IZ_2_REFLECTION_MATRIX_H
#define IZ_2_REFLECTION_MATRIX_H

#include "matrix_memory.h"

int matrix_reflection(int** arr, const int* row, const int* col, int** arr_tr);
int matrix_reflection_stream(FILE* input, FILE* output);
int matrix_reflection_file(const char* file_name_input, const char* file_name_output);
int** matrix_read(FILE* stream, int* row, int* col);
void matrix_write(FILE* stream, int** arr, const int* row, const int* col);

#endif //IZ_2_REFLECTION_MATRIX_H
