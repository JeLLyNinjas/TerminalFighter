#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <SDL.h>

#include "../src/Universe.h"
#include "mocks/MockGraphicsHandler.h"
#include "mocks/MockGameObject.h"
#include "mocks/MockUpdatable.h"

using ::testing::_;
using ::testing::Mock;

class UniverseTest : public ::testing::Test {
protected:
    Universe universe_;
    MockGraphicsHandler graphics_;

    UniverseTest()
        : universe_(graphics_) {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    virtual MockGameObject& add_game_object() {
        MockGameObject* gameobject = new MockGameObject();
        std::unique_ptr<GameObject> game_object_ptr(gameobject);
        universe_.add_game_object(std::move(game_object_ptr));
        return *gameobject;
    }
};

TEST_F(UniverseTest, game_service_update) {
    MockUpdatable* service = new MockUpdatable();
    std::unique_ptr<I_Updatable> service_ptr(service);
    EXPECT_CALL(*service, update());
    universe_.add_game_service(std::move(service_ptr));
    universe_.update_all();
}

TEST_F(UniverseTest, game_object_update) {
    MockGameObject& obj = this->add_game_object();
    EXPECT_CALL(obj, update());
    universe_.update_all();
}

TEST_F(UniverseTest, draw_all) {
    MockGameObject& obj = this->add_game_object();
    EXPECT_CALL(obj, draw(_));
    universe_.draw_all();
}

TEST_F(UniverseTest, draw_to_Screen) {
    EXPECT_CALL(graphics_, update_screen());
    universe_.draw_to_screen();
}

TEST_F(UniverseTest, update_on_destroyed) {
    MockGameObject& obj1 = this->add_game_object();
    EXPECT_CALL(obj1, update());
    EXPECT_CALL(obj1, Die());
    universe_.object_destroyed(obj1.id());
    MockGameObject& obj2 = this->add_game_object();
    EXPECT_CALL(obj2, update());
    EXPECT_CALL(obj2, Die());
    universe_.object_destroyed(obj2.id());
    universe_.object_destroyed(obj1.id());
    universe_.update_all();
    EXPECT_TRUE(Mock::VerifyAndClear(&obj1));
    EXPECT_TRUE(Mock::VerifyAndClear(&obj2));
}

TEST_F(UniverseTest, destroyed_twice) {
    MockGameObject& obj = this->add_game_object();
    EXPECT_CALL(obj, update());
    EXPECT_CALL(obj, Die()); // Expect only once
    universe_.object_destroyed(obj.id());
    universe_.object_destroyed(obj.id());
    universe_.update_all();
    EXPECT_TRUE(Mock::VerifyAndClear(&obj));
}
