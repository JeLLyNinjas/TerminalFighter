#include "gtest/gtest.h"

#include "hitbox.h"
//#include <SDL2/SDL.h>

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

TEST (HitboxTest, hitbox_overlapping_enclosed) {
    Hitbox hitbox1 = Hitbox(0, 0, 100, 100);
    Hitbox hitbox2 = Hitbox(1, 1, 50, 50);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST (HitboxTest, rect_member_constructor) {
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

TEST (HitboxTest, circle_member_constructor) {
    Hitbox hitbox1 = Hitbox(20, 30, 5);
    EXPECT_EQ(hitbox1.hitbox_circle().x, 20);
    EXPECT_EQ(hitbox1.hitbox_circle().y, 30);
    EXPECT_EQ(hitbox1.hitbox_circle().r, 5);
}

TEST (HitboxTest, Circle_circle_construtor) {
    Circle circle1 = {20, 30, 5};
    Hitbox hitbox1 = Hitbox(circle1);
    EXPECT_EQ(hitbox1.hitbox_circle().x, 20);
    EXPECT_EQ(hitbox1.hitbox_circle().y, 30);
    EXPECT_EQ(hitbox1.hitbox_circle().r, 5);
}

TEST (HitboxTest, circle_circle_touching_true) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(20, 20, 10);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_circle_overlapping_false) {
    Hitbox hitbox1 = Hitbox(10, 10, 2);
    Hitbox hitbox2 = Hitbox(40, 40, 2);
    bool expected = false;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_circle_overlapping_true) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(20, 20, 15);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_circle_enclosed) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(10, 10, 5);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_rect_touching) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(20, 0, 10, 20);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_rect_overlapping_true) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(10, 0, 20, 20);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_rect_overlapping_false) {
    Hitbox hitbox1 = Hitbox(10, 10, 10);
    Hitbox hitbox2 = Hitbox(40, 40, 20, 20);
    bool expected = false;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_rect_enclosed) {
    Hitbox hitbox1 = Hitbox(20, 20, 20);
    Hitbox hitbox2 = Hitbox(15, 15, 5);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}

TEST(HitboxTest, circle_rect_corner) {
    Hitbox hitbox1 = Hitbox(0, 0, 10, 10);
    Hitbox hitbox2 = Hitbox(14, 13, 5);
    bool expected = true;
    bool actual = hitbox1.is_overlapping(hitbox2);
    EXPECT_EQ(expected, actual);
}
