#include "gtest/gtest.h"
#include "hitbox.h"

class HitboxTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

TEST (HitboxTest, simple_test){
    Hitbox* hitbox1 = new Hitbox(0, 0, 100, 100);
    Hitbox* hitbox2 = new Hitbox(50, 50, 100, 100);
    bool expected = true;
    bool actual = Hitbox::is_overlapping(*hitbox1, *hitbox2);
    EXPECT_EQ(expected, actual);   
}

TEST (HitboxTest, bad_test){
    Hitbox* hitbox1 = new Hitbox(0, 0, 100, 100);
    Hitbox* hitbox2 = new Hitbox(50, 50, 100, 100);
    bool expected = false;
    bool actual = Hitbox::is_overlapping(*hitbox1, *hitbox2);
    EXPECT_EQ(expected, actual);   
}