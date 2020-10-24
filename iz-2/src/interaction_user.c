#include "reflection_matrix.h"

int** matrix_read(FILE* stream, int* row, int* col) {
    if(stream == NULL)
        stream = stdin;

    fscanf(stream, "%d%d", row, col);

    int **arr = get_mem(row, col);
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < *row; i++)
        for (int j = 0; j < *col; j++)
            arr[i][j] = 0;

    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            if (fscanf(stream, "%d", &arr[i][j]) == EOF) {
                arr[i][j] = 0;
                fprintf(stderr, "Failed end to file\n");
                return arr;
            }
        }
    }

    return arr;
}

void matrix_write(FILE* stream, int** arr, const int* row, const int* col) {
    if(stream == NULL)
        stream = stdout;

    fprintf(stream, "%d %d\n", *row, *col);

    for( int i = 0; i < *row; ++i ) {
        for ( int j = 0; j < *col; ++j )
            fprintf(stream, "%d ", arr[i][j]);
        fprintf(stream, "\n");
    }
}

int matrix_reflection_file(const char * file_name_input, const char * file_name_output) {
    FILE *file_input = fopen(file_name_input, "r");
    if (!file_input) {
        fprintf(stderr, "Failed to open file for read\n");
        return 1;
    }

    FILE *file_output = fopen(file_name_output, "w");
    if (!file_output) {
        fprintf(stderr, "Failed to open file for write\n");

        if (fclose(file_input))
            fprintf( stderr, "Failed to close file\n" );

        return 1;
    }

    int res = matrix_reflection_stream(file_input, file_output);

    if (fclose(file_input) || fclose(file_output)) {
        fprintf( stderr, "Failed to close file\n" );
        return 1;
    }

    return res;
}

int matrix_reflection_stream(FILE* input, FILE* output) {
    int row = 0, col = 0;
    int** arr = matrix_read(input, &row, &col);
    if (arr == NULL)
        return 1;

    int** arr_tr = get_mem(&col, &row);
    if (arr_tr == NULL) {
        clear_mem(arr, &row);
        return 1;
    }

    matrix_reflection(arr, &row, &col, arr_tr);
    clear_mem(arr, &row);

    matrix_write(output, arr_tr, &col, &row);

    clear_mem(arr_tr, &col);

    return 0;
}