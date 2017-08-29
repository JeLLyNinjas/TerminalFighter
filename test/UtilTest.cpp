#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Util/Util.h"

using ::testing::_;

class UtilTest : public ::testing::Test {
protected:
    UtilTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


TEST_F(UtilTest, test_inverse_sqrt_5) {
    EXPECT_FLOAT_EQ(util::inverse_sqrt(5), 0.44714102);
}

TEST_F(UtilTest, test_inverse_sqrt_30) {
    EXPECT_FLOAT_EQ(util::inverse_sqrt(30), 0.18242164);
}
