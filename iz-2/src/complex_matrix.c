
#include "stdio.h"
#include <stdio.h>
#include <string.h>
#include "matrix_memory.h"
#include <pthread.h>

// структура для передачи информации в поток
typedef struct {
    int** arr;
    int row;
    int col;
    int** arr_tr;
    int col_on_thread;
    int number_thread;
} Data_thread;


// читаем файл с информацией о ядрах Linux
int get_number_cores() {
    char str[256];
    int procCount = 0;
    FILE *fp;

    if( (fp = fopen("/proc/cpuinfo", "r")) )
    {
        while(fgets(str, sizeof str, fp)) {
            if (!memcmp(str, "processor", 9)) procCount++;
        }
        fclose(fp);
    }

    if ( !procCount )
    {
        procCount=2;
    }

    return procCount;
}


void* part_matrix_reflection (void* _data) {
    Data_thread* data = (Data_thread*) _data;

    // математические вычисления для определения области памяти в которой
    // должен работать поток
    int start_col = data->col - 1 - data->number_thread * data->col_on_thread;
    int end_col = data->col - (data->number_thread + 1) * data->col_on_thread;
    int new_row_i = data->number_thread * data->col_on_thread;

    for( int i = start_col; i >= end_col; --i, ++new_row_i ) {
        for ( int j = data->row - 1, new_col_j = 0; j >= 0; --j, ++new_col_j )
            data->arr_tr[new_row_i][new_col_j] = data->arr[j][i];
    }

    free(data);

    return NULL;
}

int matrix_reflection(int** arr, const int* row, const int* col, int** arr_tr) {
    int max_thread = get_number_cores() - 1;
    int col_on_thread = *col / max_thread;
    int col_on_main_thread = *col % max_thread;

    if (*col < max_thread) {
        max_thread = *col;
        col_on_thread = 1;
        col_on_main_thread = 0;
    }

    pthread_t thread_ids[max_thread];

    for (int i = 0; i < max_thread; i++) {

        Data_thread *data = (Data_thread*) malloc(sizeof(Data_thread));
        data->arr = arr;
        data->row = *row;
        data->col = *col;
        data->arr_tr = arr_tr;
        data->col_on_thread = col_on_thread;
        data->number_thread = i;

        pthread_create(&thread_ids[i], NULL, part_matrix_reflection, (void*) data);
    }


    // заполнение матрицы, которая не заполнилась потоками
    int start_col = col_on_main_thread - 1;
    int end_col = 0;
    int new_row_i = *col - col_on_main_thread;
    for( int i = start_col; i >= end_col; --i, ++new_row_i ) {
        for ( int j = *row - 1, new_col_j = 0; j >= 0; --j, ++new_col_j )
            arr_tr[new_row_i][new_col_j] = arr[j][i];
    }

    for (int i = 0; i < max_thread; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    return 0;
}

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
