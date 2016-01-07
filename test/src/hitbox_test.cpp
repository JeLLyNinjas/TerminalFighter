#include "gtest/gtest.h"

#include "hitbox.h"
#include <SDL2/SDL.h>

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

TEST (HitboxTest, constructor_1) {
    Hitbox hitbox1 = Hitbox(0, 0, 100, 100);
    bool actual, expected = true;
    if (hitbox1.hitbox().x == 0 && hitbox1.hitbox().y == 0 && hitbox1.hitbox().w == 100 && hitbox1.hitbox().h == 100)
    	actual = true;
    else 
    	actual = false;
    EXPECT_EQ(expected, actual);
}

TEST (HitboxTest, constructor_2) {
    SDL_Rect rect1 = {0, 0, 100, 100};
    Hitbox hitbox1 = Hitbox(rect1);
    bool actual, expected = true;
    if (hitbox1.hitbox().x == 0 && hitbox1.hitbox().y == 0 && hitbox1.hitbox().w == 100 && hitbox1.hitbox().h == 100)
    	actual = true;
    else
    	actual = false;
    EXPECT_EQ(expected, actual);
}
