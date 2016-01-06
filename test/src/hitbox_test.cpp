#include "gtest/gtest.h"

#include "hitbox.h"

class HitboxTest : public ::testing::Test {
protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST (HitboxTest, simple_hitbox_overlapping_true) {
    Hitbox hitbox1 = Hitbox(0, 0, 100, 100);
    Hitbox hitbox2 = Hitbox(50, 50, 100, 100);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST (HitboxTest, simple_hitbox_overlapping_false) {
    Hitbox hitbox1 = Hitbox(0, 0, 100, 100);
    Hitbox hitbox2 = Hitbox(101, 0, 100, 100);
    bool expected = false;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}
