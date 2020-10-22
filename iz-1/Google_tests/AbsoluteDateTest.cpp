#include "gtest/gtest.h"

extern "C" {
#include "../include/logic.h"
}

#define DELTA 0.0001

TEST(AbsoluteDateTestSuite, ExampleDate_1){ // (0, 0),(0, 4),(3, 0) -> 6

    const size_t LEN_MAS = 3;

    float test_x_y[2][LEN_MAS] = {{0, 0, 3}, {0, 4, 0}};
    const float EXPECTED = 6;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }
    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_NEAR(EXPECTED, *res, DELTA);
    free(res);
}

TEST(AbsoluteDateTestSuite, ExampleDate_2){ // (-2, -2),(-2, 2),(2, 2),(2, -2) -> 16
    const size_t LEN_MAS = 4;

    float test_x_y[2][LEN_MAS] = {{-2, -2, 2, 2}, {-2, 2, 2, -2}};
    const float EXPECTED = 16;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }
    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_NEAR(EXPECTED, *res, DELTA);
    free(res);
}

TEST(AbsoluteDateTestSuite, ExampleDate_3){ // (-2, -2),(-1, 1),(1, 3),(3, 3),(5, 1),(2, -1) -> 19.5
    const size_t LEN_MAS = 6;

    float test_x_y[2][LEN_MAS] = {{-2, -1, 1, 3, 5, 2}, {-2, 1, 3, 3, 1, -1}};
    const float EXPECTED = 19.5;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }
    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_NEAR(EXPECTED, *res, DELTA);
    free(res);
}


TEST(AbsoluteDateTestSuite, ExampleDate_4){ // (1, 1),(3, 3),(5, 5) -> 0 // на одной прямой
    const size_t LEN_MAS = 3;
    float test_x_y[2][LEN_MAS] = {{1, 3, 5}, {1, 3, 5}};
    const auto EXPECTED = 0;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }

    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_NEAR(EXPECTED, *res, DELTA);
    free(res);
}


TEST(AbsoluteDateTestSuite, IncorrectDate_1){ // (-2, -2),(-1, 1),(1, 3),(3, 3),(5, 1),(NULL, -1) -> NULL
    const size_t LEN_MAS = 6;
    float test_x_y[2][LEN_MAS] = {{-2, -1, 1, 3, 5, 2}, {-2, 1, 3, 3, 1, -1}};
    const auto EXPECTED = nullptr;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }
    test_x[LEN_MAS - 1] = nullptr;
    test_y[LEN_MAS - 1] = &test_x_y[1][LEN_MAS - 1];

    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_EQ(EXPECTED, res);
}

TEST(AbsoluteDateTestSuite, IncorrectDate_2){ // (-0.5, 0.43),(-1, 1) -> NULL
    const size_t LEN_MAS = 2;
    float test_x_y[2][LEN_MAS] = {{-0.5, -1}, {0.43, 1}};
    const auto EXPECTED = nullptr;

    float *test_x[LEN_MAS];
    float *test_y[LEN_MAS];
    for (int i = 0; i < LEN_MAS; i++)
    {
        test_x[i] = &test_x_y[0][i];
        test_y[i] = &test_x_y[1][i];
    }

    float *res = area_figure(test_x, test_y, LEN_MAS);

    ASSERT_EQ(EXPECTED, res);
}