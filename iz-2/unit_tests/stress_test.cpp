#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <dlfcn.h>
#include <chrono>

extern "C" {
#include "reflection_matrix.h"
}

using namespace std::chrono;

int generate_matrix(const char* NAME_INPUT, const int ROW, const int COL) {
    FILE *file = fopen(NAME_INPUT, "w");
    if(!file) {
        fprintf(stderr, "library opening failed");
        return 1;
    }

    srand ( time(nullptr) );

    fprintf(file, "%d %d\n", ROW, COL);
    for(int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            fprintf(file, "%d", 10 + rand() % 90);
            if (j < COL - 1)
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    if(fclose(file)) {
        fprintf(stderr, "library close failed");
        return 1;
    }

    return 0;
}

int compare_file(const char* NAME_FIRST, const char* NAME_SECOND) {
    std::string line_consistent, line_parallel;

    std::ifstream in_consistent(NAME_FIRST);
    std::ifstream in_parallel(NAME_SECOND);
    if (!in_consistent.is_open() || !in_parallel.is_open())
    {
        std::cerr << "TEST Failed to open file";
        in_consistent.close();
        in_parallel.close();
        return 1;
    }

    while (getline(in_consistent, line_parallel) && getline(in_parallel, line_consistent))
    {
        if(line_consistent != line_parallel) {
            in_consistent.close();
            in_parallel.close();
            return 1;
        }
    }

    in_consistent.close();
    in_parallel.close();

    return 0;
}

TEST(StressTest, BigMatrix){
    const char* NAME_INPUT = "../unit_tests/stress_test_files/test.input";
    const char* NAME_CONSISTENT_OUTPUT = "../unit_tests/stress_test_files/test_consistent.output";
    const char* NAME_PARALLEL_OUTPUT = "../unit_tests/stress_test_files/test_parallel.output";


    const int ROW = 10000;
    const int COL = 5000;

    generate_matrix(NAME_INPUT, ROW, COL);


    // запускаем функцию из статической библиотеки
    matrix_reflection_file(NAME_INPUT, NAME_CONSISTENT_OUTPUT);


    void *library;
    int (*dynamic_func)(const char* file_name_input, const char* file_name_output);

    library = dlopen("./libcomplex_matrix_lib.so", RTLD_LAZY); // подключение библиотеки
    if (!library) {
        fprintf(stderr, "library opening failed");
        ASSERT_TRUE(false);
    }

    void* func = dlsym(library, "matrix_reflection_file");
    dynamic_func = (int (*)(const char *, const char *)) func;


    // зпускаем функцию из динамической библиотеки
    (*dynamic_func)(NAME_INPUT, NAME_PARALLEL_OUTPUT);

    dlclose(library);


    // сравниваем результаты
    ASSERT_TRUE(compare_file(NAME_CONSISTENT_OUTPUT, NAME_PARALLEL_OUTPUT) == 0);
}

// В этом тесте происходит замер времени и его сравнивание.
// Для корректного подсчета времени замеряем только работу алгоритма,
// без чтения и записи в файл
TEST(StressTest, MiddleMatrix){
    const char* NAME_INPUT = "../unit_tests/stress_test_files/test.input";
    const char* NAME_CONSISTENT_OUTPUT = "../unit_tests/stress_test_files/test_consistent.output";
    const char* NAME_PARALLEL_OUTPUT = "../unit_tests/stress_test_files/test_parallel.output";

    const int RETRIES = 5;

    const int ROW = 2000;
    const int COL = 3000;


    // подключение динамической библиотеки
    void *library;
    int (*dynamic_func)(int**, int*, int*, int**);

    library = dlopen("./libcomplex_matrix_lib.so", RTLD_LAZY);
    if (!library) {
        fprintf(stderr, "library opening failed");
        ASSERT_TRUE(false);
    }

    void* func = dlsym(library, "matrix_reflection");
    dynamic_func = (int (*)(int**, int*, int*, int**)) func;


    duration<double> time_consistent{};
    duration<double> time_parallel{};
    for (int i = 0; i < RETRIES; ++i) {
        ASSERT_TRUE(generate_matrix(NAME_INPUT, ROW, COL) == 0);

        FILE *file_input = fopen(NAME_INPUT, "r");
        FILE *file_consistent_output = fopen(NAME_CONSISTENT_OUTPUT, "w");
        FILE *file_parallel_output = fopen(NAME_PARALLEL_OUTPUT, "w");

        int row = 0, col = 0;
        int** arr = matrix_read(file_input, &row, &col);
        int** arr_tr = get_mem(&col, &row);


        // последовательная реализация
        system_clock::time_point begin = system_clock::now();
        matrix_reflection(arr, &row, &col, arr_tr);
        system_clock::time_point end = system_clock::now();
        time_consistent += end - begin;

        matrix_write(file_consistent_output, arr_tr, &col, &row);


        // параллельная реализация
        begin = system_clock::now();
        (*dynamic_func)(arr, &row, &col, arr_tr);
        end = system_clock::now();
        time_parallel += end - begin;

        matrix_write(file_parallel_output, arr_tr, &col, &row);


        // очистка памяти
        clear_mem(arr, &row);
        clear_mem(arr_tr, &col);

        fclose(file_input);
        fclose(file_consistent_output);
        fclose(file_parallel_output);

        // сравнение результатов
        ASSERT_TRUE(compare_file(NAME_CONSISTENT_OUTPUT, NAME_PARALLEL_OUTPUT) == 0);
    }

    duration<double> consistent = time_consistent / RETRIES;
    std::cout << "consistent: " << consistent.count() << std::endl;

    duration<double> parallel = time_parallel / RETRIES;
    std::cout << "parallel: " << parallel.count() << std::endl;


    dlclose(library); // закрытие динамической библиотеки
}