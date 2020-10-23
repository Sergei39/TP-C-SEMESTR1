
#include "naive_matrix.h"
#include "matrix_member.h"

int main() {

    int row = 0, col = 0;

    int** arr = matrix_read(stdin, &row, &col);
    matrix_reflection_and_write(stdout, arr, &row, &col);

    clear_mem(arr, &row);

    return 0;
}
