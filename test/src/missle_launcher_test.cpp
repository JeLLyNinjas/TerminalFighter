#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "missile_launcher.h"
#include "mocks/mock_missile_launcher_listener.h"

using ::testing::_;

class MissleLauncherTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        MissileLauncher launcher;
        MockMissileLauncherListener launcher_listener;
        launcher.add_listener(&launcher_listener);
    }

    virtual void TearDown() {
    }
};

TEST(MissileLauncherTest, multiple_listeners_notified) {
    MockMissileLauncherListener launcher_listener2;

    EXPECT_CALL(launcher_listener1, notify_missile_launched(_))
    EXPECT_CALL(launcher_listener2, notify_missile_launched(_))

    launcher.add_listener(&launcher_listener2);
    launcher.create_missile(0, 0, 0, 0);
}

TEST(MissileLauncherTest, listeners_multiple_notifications) {
    EXPECT_CALL(launcher_listener, notify_missile_launched(_))
        .Times(3);

    launcher.create_missile(0, 0, 0, 0);
    launcher.create_missile(0, 0, 0, 0);
    launcher.create_missile(0, 0, 0, 0);
}

TEST(MissileLauncherTest, correct_missile_passed) {
    EXPECT_CALL(launcher_listener, notify_missile_launched(_))
        .Times(3);

    launcher.create_missile(0, 0, 0, 0);
    launcher.create_missile(0, 0, 0, 0);
    launcher.create_missile(0, 0, 0, 0);
}