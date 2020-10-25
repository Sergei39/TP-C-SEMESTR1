#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>


TEST(StressTest, BigMatrix){
    char* NAME_INPUT = "../unit_tests/stress_test_files/test.input";
    char* NAME_CONSISTENT_OUTPUT = "../unit_tests/stress_test_files/test_consistent.output";
    char* NAME_PARALLEL_OUTPUT = "../unit_tests/stress_test_files/test_parallel.output";


    const int ROW = 10000;
    const int COL = 5000;
    FILE *file = fopen(NAME_INPUT, "w");
    if(!file) {
        std::cerr << "TEST Failed to open file";
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

    /*Spawn a child to run the program.*/
    pid_t pid1=fork();
    if (pid1==0) { /* child process */
        static char *argv[]={NAME_INPUT, NAME_CONSISTENT_OUTPUT, nullptr};
        execv("iz-2-consistent",argv);
        exit(127); /* only if execv fails */
    }
    pid_t pid2=fork();
    if (pid2==0) {  /* child process */
        static char *argv[] = {NAME_INPUT, NAME_PARALLEL_OUTPUT, nullptr};
        execv("iz-2-parallel", argv);
        exit(127); /* only if execv fails */
    }

    waitpid(pid1,nullptr,0); /* wait for child to exit */
    waitpid(pid2,nullptr,0); /* wait for child to exit */
    

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