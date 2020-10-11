#include "gtest/gtest.h"

extern "C" {
#include "../include/logic.h"
}

#define MAX_POINT 10

TEST(AbsoluteDateTestSuite, ExampleDate_1){ // 12/2/2020 -> 737761

    float *x[MAX_POINT], *y[MAX_POINT];
    for(int i = 0; i < MAX_POINT; i++){
        x[i] = (float*) malloc(sizeof(float));
        y[i] = (float*) malloc(sizeof(float));
    }

    *x[0] = 0; *x[1] = 0; *x[2] = 3;
    *y[0] = 0; *y[1] = 4; *y[2] = 0;

    float *res = area_figure(x, 3, y, 3);

    ASSERT_NEAR(6, *res, 0.001);

    free(res);

    for(int i = 0; i < MAX_POINT; i++) {
        free(x[i]);
        free(y[i]);
    }
}
TEST(AbsoluteDateTestSuite, ExampleDate_2){ // 12/2/2020 -> 737761
    const size_t len_mas = 4;
    float test_x_y[2][len_mas] = {{-2, -2, 2, 2}, {-2, 2, 2, -2}};
    float *test_x[len_mas] = {&test_x_y[0][0], &test_x_y[0][1], &test_x_y[0][2], &test_x_y[0][3]};
    float *test_y[len_mas] = {&test_x_y[1][0], &test_x_y[1][1], &test_x_y[1][2], &test_x_y[1][3]};
    float *res = area_figure(test_x, len_mas, test_y, len_mas);

    ASSERT_NEAR(16, *res, 0.001);
    free(res);
}


//TEST(AbsoluteDateTestSuite, IncorrectDate){ // 12/0/2020 -> 0
//GregorianDate gregDate;
//gregDate.SetMonth(12);
//gregDate.SetDay(0);
//gregDate.SetYear(2020);
//
//ASSERT_EQ(gregDate.getAbsoluteDate(),0);
//}