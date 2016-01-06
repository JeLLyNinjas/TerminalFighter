#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "missile_launcher.h"
#include "mocks/mock_missile_launcher_listener.h"

using ::testing::_;

class MissleLauncherTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST(MissileLauncherTest, check_listeners_notified_onlaunch) {
    MockMissileLauncherListener launcher_listener;
    EXPECT_CALL(launcher_listener, notify_missile_launched(_))
        .Times(1);

    MissileLauncher launcher;
    launcher.add_listener(&launcher_listener);
    launcher.create_missile(0, 0, 0, 0);
}