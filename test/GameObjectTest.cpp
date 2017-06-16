#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/GameObject.h"
#include "mocks/MockGameObject.h"
#include "../src/Hitbox.h"

class GameObjectTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST(GameObjectTest, incrementing_id) {
    const int NUM = 10;
    GameObject* gameobjects[NUM];

    for (int i = 0; i < NUM; i++) {
        gameobjects[i] = new MockGameObject();
    }

    int prev_id = gameobjects[0]->id();

    for (int i = 1 ; i < NUM; i++) {
        unsigned int actual = gameobjects[i]->id();
        EXPECT_EQ(prev_id + 1, actual);
        prev_id = gameobjects[i]->id();
    }
}
