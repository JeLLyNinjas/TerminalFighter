#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <SDL.h>

#include "Universe.h"
#include "mocks/MockGraphicsHandler.h"
#include "mocks/MockUpdatable.h"

class UniverseTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(UniverseTest, gameServiceUpdate) {
    MockUpdatable* service = new MockUpdatable();
    std::unique_ptr<I_Updatable> service_ptr(service);
    MockGraphicsHandler graphics;
    EXPECT_CALL(*service, update());
    Universe universe(graphics);
    universe.add_game_service(std::move(service_ptr));
    universe.update_all();
}
