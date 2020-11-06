
#include "reflection_matrix.h"

int matrix_reflection(int** arr, const int *row, const int *col, int**arr_tr) {
    for( int i = *col - 1, new_row_i = 0; i >= 0; --i, ++new_row_i ) {
        for ( int j = *row - 1, new_col_j = 0; j >= 0; --j, ++new_col_j )
            arr_tr[new_row_i][new_col_j] = arr[j][i];
    }
}
