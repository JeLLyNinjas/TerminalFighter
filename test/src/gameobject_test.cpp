#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_object.h"
#include "mocks/mock_gameobject.h"

class GameObjectTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST(GameObjectTest, check_id_start_0) {
	GameObject* gameobject = new MockGameObject();
	unsigned int expected = 0;
	unsigned int actual = gameobject->id();
	EXPECT_EQ(expected, actual);
}
