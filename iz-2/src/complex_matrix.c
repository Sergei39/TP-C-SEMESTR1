
#include "reflection_matrix.h"
#include <string.h>
#include <pthread.h>
#include <zconf.h>

// структура для передачи информации в поток
typedef struct {
    int** arr;
    int** arr_tr;
    int row;
    int col;
    int col_on_thread;
    int number_thread;
} Data_thread;


void* part_matrix_reflection (void* _data) {
    printf("Hello\n");
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
    // читаем информацию о количестве ядер в процессоре
    int max_thread = (int) sysconf(_SC_NPROCESSORS_ONLN) - 1;

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

        int err = pthread_create(&thread_ids[i], NULL, part_matrix_reflection, (void*) data);

        if (err != 0) {
            return 1;
        }
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