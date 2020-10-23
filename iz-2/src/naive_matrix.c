
#include "naive_matrix.h"

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

int** matrix_read_file(const char* file_name, int* row, int* col) {
    FILE *file = fopen(file_name, "r");

    if (!file) {
        fprintf(stderr, "Failed to open file for write\n");
        return NULL;
    }

    int** arr = matrix_read(file, row, col);

    if (fclose(file)) {
        fprintf( stderr, "Failed to close file\n" );
        return NULL;
    }

    return arr;
}

void matrix_reflection_and_write(FILE* stream, int** arr, const int* row, const int* col) {
    if(stream == NULL)
        stream = stdout;

    for( int i = *col - 1; i >= 0; --i ) {
        for ( int j = *row - 1; j >= 0; --j )
            fprintf(stream, "%d ", arr[j][i]);
        fprintf(stream, "\n");
    }
}

