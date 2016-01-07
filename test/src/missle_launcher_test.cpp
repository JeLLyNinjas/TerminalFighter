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

TEST(MissileLauncherTest, multiple_listeners_notified) {
    MockMissileLauncherListener launcher_listener1;
    MockMissileLauncherListener launcher_listener2;
    EXPECT_CALL(launcher_listener1, notify_missile_launched(_))
        .Times(1);
    EXPECT_CALL(launcher_listener2, notify_missile_launched(_))
        .Times(1);

    MissileLauncher launcher;
    launcher.add_listener(&launcher_listener1);
    launcher.add_listener(&launcher_listener2);
    launcher.create_missile(0, 0, 0, 0);
}