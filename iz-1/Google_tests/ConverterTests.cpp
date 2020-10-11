#include "gtest/gtest.h"

extern "C" {
#include "logic.h"
}

#define MAX_POINT 10

class DateConverterFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
//        gregDate = new GregorianDate();
//        julDate = new JulianDate();
    }

    virtual void TearDown() {
//        delete gregDate;
//        delete julDate;
    }
//
//    GregorianDate * gregDate;
//    JulianDate * julDate;
};

TEST_F(DateConverterFixture, ExampleDate_1){ // 12/2/2020 -> 737761

    float *x[MAX_POINT], *y[MAX_POINT];
    for(int i = 0; i < MAX_POINT; i++){
        x[i] = (float*) malloc(sizeof(float));
        y[i] = (float*) malloc(sizeof(float));
    }

    *x[0] = 0; *x[1] = 0; *x[2] = 3;
    *y[0] = 0; *y[1] = 4; *y[2] = 0;

    float *res = area_figure(x, 3, y, 3);

    ASSERT_NEAR(5, *res, 0.001);

    free(res);

    for(int i = 0; i < MAX_POINT; i++) {
        free(x[i]);
        free(y[i]);
    }
}
//
//
//TEST(logic, ok) {
//    float test_x[1][3] = {{0, 3, 0}};
//    float test_y[1][3] = {{0, 0, 4}};
//    float *test_res = area_figure(test_x, 3, test_y, 3);
//
//    ASSERT_NEAR(6, *test_res, 0.01);
//}
//
//TEST_F(DateConverterFixture, FirstDayEver){ // 1/1/1 -> 1/3/1
//
//gregDate->SetMonth(1);
//gregDate->SetDay(1);
//gregDate->SetYear(1);
//
//int absGregDate = gregDate->getAbsoluteDate();
//julDate->CalcJulianDate(absGregDate);
//
//EXPECT_EQ(julDate->getMonth(),1);
//EXPECT_EQ(julDate->getDay(),3);
//EXPECT_EQ(julDate->getYear(),1);
//
//}
//
//TEST_F(DateConverterFixture, PlusOneDiff){ // 3/1/100 -> 3/2/100
//
//gregDate->SetMonth(3);
//gregDate->SetDay(1);
//gregDate->SetYear(100);
//
//int absGregDate = gregDate->getAbsoluteDate();
//julDate->CalcJulianDate(absGregDate);
//
//EXPECT_EQ(julDate->getMonth(),3);
//EXPECT_EQ(julDate->getDay(),2);
//EXPECT_EQ(julDate->getYear(),100);
//}
//
//TEST_F(DateConverterFixture, MinusOne_Leap){ // 3/1/300 -> 2/29/300
//
//gregDate->SetMonth(3);
//gregDate->SetDay(1);
//gregDate->SetYear(300);
//
//int absGregDate = gregDate->getAbsoluteDate();
//julDate->CalcJulianDate(absGregDate);
//
//EXPECT_EQ(julDate->getMonth(),2);
//EXPECT_EQ(julDate->getDay(),29);
//EXPECT_EQ(julDate->getYear(),300);
//}
//
//
//TEST_F(DateConverterFixture, PlusFour_Leap){ // 3/1/900 -> 2/25/900
//
//gregDate->SetMonth(3);
//gregDate->SetDay(1);
//gregDate->SetYear(900);
//
//int absGregDate = gregDate->getAbsoluteDate();
//julDate->CalcJulianDate(absGregDate);
//
//EXPECT_EQ(julDate->getMonth(),2);
//EXPECT_EQ(julDate->getDay(),25);
//EXPECT_EQ(julDate->getYear(),900);
//}