#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <dlfcn.h>

extern "C" {
#include "reflection_matrix.h"
}


TEST(CorrectTestLib, SmallMatrix){
    const char* NAME_INPUT = "../unit_tests/test_files/small_matrix.input";
    const char* NAME_EXPECTED_OUTPUT = "../unit_tests/test_files/small_matrix.output";
    const char* NAME_OUTPUT = "../unit_tests/test_files/output.output";
    matrix_reflection_file(NAME_INPUT, NAME_OUTPUT);

    std::string line_expected, line_test;

    std::ifstream in(NAME_OUTPUT);
    std::ifstream ex_in(NAME_EXPECTED_OUTPUT);
    if (!in.is_open() || !ex_in.is_open())
    {
        std::cerr << "TEST Failed to open file";
        in.close();
        ex_in.close();
        ASSERT_TRUE(false);
    }

    while (getline(in, line_test) && getline(ex_in, line_expected))
    {
        ASSERT_TRUE(line_expected == line_test);
    }
    in.close();
    ex_in.close();
}

TEST(IncorrectTestLib, IncorrectNameFile){
    const char* NAME_INPUT = "big_matrix.input";
    const char* NAME_OUTPUT = "../unit_tests/test_files/output.output";
    const int EXPECTED = 1;

    int res = matrix_reflection_file(NAME_INPUT, NAME_OUTPUT);

    ASSERT_EQ(EXPECTED, res);
}

TEST(IncorrectTestLib, BrokenMatrix){
    const char* NAME_INPUT = "../unit_tests/incorrect_files/broken_matrix.input";
    const char* NAME_EXPECTED_OUTPUT = "../unit_tests/incorrect_files/broken_matrix.output";
    const char* NAME_OUTPUT = "../unit_tests/test_files/output.output";
    matrix_reflection_file(NAME_INPUT, NAME_OUTPUT);

    std::string line_expected, line_test;

    std::ifstream in(NAME_OUTPUT);
    std::ifstream ex_in(NAME_EXPECTED_OUTPUT);
    if (!in.is_open() || !ex_in.is_open())
    {
        std::cerr << "TEST Failed to open file";
        in.close();
        ex_in.close();
        ASSERT_TRUE(false);
    }

    while (getline(in, line_test) && getline(ex_in, line_expected))
    {
        ASSERT_TRUE(line_expected == line_test);
    }
    in.close();
    ex_in.close();
}