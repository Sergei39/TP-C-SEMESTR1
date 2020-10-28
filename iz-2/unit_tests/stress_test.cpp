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

TEST(StressTest, BigMatrix){
    const char* NAME_INPUT = "../unit_tests/stress_test_files/test.input";
    const char* NAME_CONSISTENT_OUTPUT = "../unit_tests/stress_test_files/test_consistent.output";
    const char* NAME_PARALLEL_OUTPUT = "../unit_tests/stress_test_files/test_parallel.output";


    const int ROW = 10000;
    const int COL = 5000;
    FILE *file = fopen(NAME_INPUT, "w");
    if(!file) {
        fprintf(stderr, "library opening failed");
        ASSERT_TRUE(false);
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

    fclose(file);

    // запускаем функцию из статической библиотеки и мерим время
    system_clock::time_point start = system_clock::now();
    matrix_reflection_file(NAME_INPUT, NAME_CONSISTENT_OUTPUT);
    system_clock::time_point end = system_clock::now();
    duration<double> consistent = end - start;
    std::cout << "consistent: " << consistent.count() << std::endl;


    void *library;
    int (*dynamic_func)(const char* file_name_input, const char* file_name_output);

    library = dlopen("./libcomplex_matrix_lib.so", RTLD_LAZY); // подключение библиотеки
    if (!library) {
        fprintf(stderr, "library opening failed");
        ASSERT_TRUE(false);
    }

    void* func = dlsym(library, "matrix_reflection_file");
    dynamic_func = (int (*)(const char *, const char *)) func;


    // зпускаем функцию из динамической библиотеки и мерим время
    start = system_clock::now();
    (*dynamic_func)(NAME_INPUT, NAME_PARALLEL_OUTPUT);
    end = system_clock::now();
    duration<double> parallel = end - start;
    std::cout << "parallel: " << parallel.count() << std::endl;

    dlclose(library);


    // сравниваем результаты
    std::string line_consistent, line_parallel;

    std::ifstream in_consistent(NAME_CONSISTENT_OUTPUT);
    std::ifstream in_parallel(NAME_PARALLEL_OUTPUT);
    if (!in_consistent.is_open() || !in_parallel.is_open())
    {
        std::cerr << "TEST Failed to open file";
        in_consistent.close();
        in_parallel.close();
        ASSERT_TRUE(false);
    }

    while (getline(in_consistent, line_parallel) && getline(in_parallel, line_consistent))
    {
        ASSERT_TRUE(line_consistent == line_parallel);
    }
    in_consistent.close();
    in_parallel.close();

    remove(NAME_INPUT);
    remove(NAME_PARALLEL_OUTPUT);
    remove(NAME_CONSISTENT_OUTPUT);
}