#include <math.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Util/Util.h"



using ::testing::_;

namespace {
    const double ANGLE_START_X = 100.0;
    const double ANGLE_START_Y = 100.0;
    const double ANGLE_PT_INCREMENT = 50.0;
}

class UtilTest : public ::testing::Test {
protected:
    UtilTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

// Converts an angle to be between 0 and 360
double standardize_angle(double angle) {
    double standard_angle = angle;

    while (standard_angle < 0) {
        standard_angle += 360;
    }

    return fmod(standard_angle, 360);
}

TEST_F(UtilTest, test_inverse_sqrt_5) {
    EXPECT_FLOAT_EQ(util::inverse_sqrt(5), 0.44714102);
}

TEST_F(UtilTest, test_inverse_sqrt_30) {
    EXPECT_FLOAT_EQ(util::inverse_sqrt(30), 0.18242164);
}

TEST_F(UtilTest, test_clock_angle_north) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X + 0,
                                      ANGLE_START_Y + ANGLE_PT_INCREMENT));
    EXPECT_FLOAT_EQ(result, 180.0);
}

TEST_F(UtilTest, test_clock_angle_northeast) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X + ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y + ANGLE_PT_INCREMENT));
    EXPECT_FLOAT_EQ(result, 135.0);
}

TEST_F(UtilTest, test_clock_angle_east) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X + ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y + 0));
    EXPECT_FLOAT_EQ(result, 90.0);
}

TEST_F(UtilTest, test_clock_angle_southeast) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X + ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y - ANGLE_PT_INCREMENT));
    EXPECT_FLOAT_EQ(result, 45.0);
}

TEST_F(UtilTest, test_clock_angle_south) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X + 0,
                                      ANGLE_START_Y - ANGLE_PT_INCREMENT));

    // should be 0 or 360, both are acceptable answers
    if (result > 180) {
        EXPECT_NEAR(result, 360, 0.001);
    } else {
        EXPECT_NEAR(result, 0, 0.001);
    }
}

TEST_F(UtilTest, test_clock_angle_southwest) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X - ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y - ANGLE_PT_INCREMENT));
    EXPECT_FLOAT_EQ(result, 315.0);
}

TEST_F(UtilTest, test_clock_angle_west) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X - ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y + 0));
    EXPECT_FLOAT_EQ(result, 270);
}

TEST_F(UtilTest, test_clock_angle_northwest) {
    double result = standardize_angle(util::angle(ANGLE_START_X,
                                      ANGLE_START_Y,
                                      ANGLE_START_X - ANGLE_PT_INCREMENT,
                                      ANGLE_START_Y + ANGLE_PT_INCREMENT));
    EXPECT_FLOAT_EQ(result, 225.0);
}
