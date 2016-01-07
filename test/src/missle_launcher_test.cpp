#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "missile_launcher.h"
#include "mocks/mock_missile_launcher_listener.h"

using ::testing::_;
using ::testing::Property;

class MissileLauncherTest : public ::testing::Test {
protected:
    MissileLauncher* launcher;
    MockMissileLauncherListener* launcher_listener;

    virtual void SetUp() {
        launcher = new MissileLauncher() ;
        launcher_listener = new MockMissileLauncherListener();
        launcher->add_listener(launcher_listener);
    }

    virtual void TearDown() {
        delete launcher_listener;
    }
};

TEST_F(MissileLauncherTest, multiple_listeners_notified) {
    MockMissileLauncherListener launcher_listener2;

    EXPECT_CALL(*launcher_listener, notify_missile_launched(_));
    EXPECT_CALL(launcher_listener2, notify_missile_launched(_));

    launcher->add_listener(&launcher_listener2);
    launcher->create_missile(0, 0, 0, 0);
}

TEST_F(MissileLauncherTest, listeners_multiple_notifications) {
    EXPECT_CALL(*launcher_listener, notify_missile_launched(_))
    .Times(3);

    launcher->create_missile(0, 0, 0, 0);
    launcher->create_missile(0, 0, 0, 0);
    launcher->create_missile(0, 0, 0, 0);
}

TEST_F(MissileLauncherTest, correct_missile_passed) {
    EXPECT_CALL(*launcher_listener,
                notify_missile_launched(AllOf(Property(&Missile::x_pos, 11.0),
                                              Property(&Missile::y_pos, 12.0),
                                              Property(&Missile::x_vel, 13.0),
                                              Property(&Missile::y_vel, 14.0))));   

    launcher->create_missile(11, 12, 13, 14);
}