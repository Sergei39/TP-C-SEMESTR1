
#include "complex_matrix.h"
#include "stdlib.h"
#include <time.h>

int main() {

//    int row = 3000;
//    int col = 6000;
//    FILE *file = fopen("../unit_tests/test_files/middle_matrix.input", "w");
//
//    srand ( time(NULL) );
//
//    fprintf(file, "%d %d\n", row, col);
//    for(int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            fprintf(file, "%d", 10 + rand() % 90);
//            if (j < col - 1)
//                fprintf(file, " ");
//        }
//        fprintf(file, "\n");
//    }
//
//    fclose(file);

//    for (int k = 0; k < 200; k++) {
//        FILE *file = fopen("../unit_tests/test_files/big_matrix.input", "a");
//
//        for(int i = 0; i < row; i++) {
//            for (int j = 0; j < col; j++) {
//                fprintf(file, "%d", 10 + rand() % 90);
//                if (j < col - 1)
//                    fprintf(file, " ");
//            }
//            fprintf(file, "\n");
//        }
//
//        fclose(file);
//    }

    //matrix_reflection_file("../unit_tests/incorrect_files/broken_matrix.input", "../unit_tests/incorrect_files/broken_matrix.output");

    int row = 7, col = 4;
    matrix_reflection(NULL, &row, &col, NULL);

    return 0;
}
