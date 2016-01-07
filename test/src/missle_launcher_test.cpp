#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_constants.h"
#include "missile_launcher.h"
#include "mocks/mock_projectile_creator_listener.h"

using ::testing::_;

class MissileLauncherTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST(MissileLauncherTest, check_listeners_notified_onlaunch) {
    MockProjectileCreatorListener launcher_listener;
    EXPECT_CALL(launcher_listener, notify_friendly_projectile_launched(_))
        .Times(1);

    MissileLauncher launcher = MissileLauncher(FRIENDLY);
    launcher.add_listener(&launcher_listener);
    launcher.create_missile(0, 0, 0, 0);
}