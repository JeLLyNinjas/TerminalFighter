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

TEST (HitboxTest, member_constructor) {
    Hitbox hitbox1 = Hitbox(0, 5, 100, 110);
    EXPECT_EQ(hitbox1.hitbox().x, 0);
    EXPECT_EQ(hitbox1.hitbox().y, 5);
    EXPECT_EQ(hitbox1.hitbox().w, 100);
    EXPECT_EQ(hitbox1.hitbox().h, 110);
}

TEST (HitboxTest, SDL_rect_constructor) {
    SDL_Rect rect1 = {0, 5, 100, 110};
    Hitbox hitbox1 = Hitbox(rect1);
    EXPECT_EQ(hitbox1.hitbox().x, 0);
    EXPECT_EQ(hitbox1.hitbox().y, 5);
    EXPECT_EQ(hitbox1.hitbox().w, 100);
    EXPECT_EQ(hitbox1.hitbox().h, 110);
}
