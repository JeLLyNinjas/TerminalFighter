#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_constants.h"
#include "missile_launcher.h"
#include "mocks/mock_projectile_creator_listener.h"

using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class MissileLauncherListenerTest : public ::testing::Test {
protected:
    MissileLauncher* launcher;
    MockProjectileCreatorListener* launcher_listener;

    virtual void SetUp() {
        launcher = new MissileLauncher(FRIENDLY) ;
        launcher_listener = new MockProjectileCreatorListener();
        launcher->add_listener(launcher_listener);
    }

    virtual void TearDown() {
        delete launcher;
        delete launcher_listener;
    }
};

TEST_F(MissileLauncherListenerTest, multiple_listeners_notified) {
    MockProjectileCreatorListener launcher_listener2;

    EXPECT_CALL(*launcher_listener, notify_projectile_launched(_, _));
    EXPECT_CALL(launcher_listener2, notify_projectile_launched(_, _));

    launcher->add_listener(&launcher_listener2);
    launcher->create_missile(0, 0, 0, 0);
}

TEST_F(MissileLauncherListenerTest, listeners_multiple_notifications) {
    EXPECT_CALL(*launcher_listener, notify_projectile_launched(_, _))
    .Times(3);

    launcher->create_missile(0, 0, 0, 0);
    launcher->create_missile(0, 0, 0, 0);
    launcher->create_missile(0, 0, 0, 0);
}

TEST_F(MissileLauncherListenerTest, correct_params_passed) {
    EXPECT_CALL(*launcher_listener,
                notify_projectile_launched(AllOf(Property(&Missile::x_pos, 11.0),
                                              Property(&Missile::y_pos, 12.0),
                                              Property(&Missile::x_vel, 13.0),
                                              Property(&Missile::y_vel, 14.0)), _));   

    launcher->create_missile(11, 12, 13, 14);
}

TEST_F(MissileLauncherListenerTest, correct_missiles_passed) {
    InSequence dummy;

    EXPECT_CALL(*launcher_listener,
                notify_projectile_launched(AllOf(Property(&Missile::x_pos, 10.0),
                                              Property(&Missile::y_pos, 10.0),
                                              Property(&Missile::x_vel, 10.0),
                                              Property(&Missile::y_vel, 10.0)), _));   
    EXPECT_CALL(*launcher_listener,
                notify_projectile_launched(AllOf(Property(&Missile::x_pos, 20.0),
                                              Property(&Missile::y_pos, 20.0),
                                              Property(&Missile::x_vel, 20.0),
                                              Property(&Missile::y_vel, 20.0)), _));   

    launcher->create_missile(10, 10, 10, 10);
    launcher->create_missile(20, 20, 20, 20);
}

TEST(MissileLauncherTeamTest, team_set) {
    MissileLauncher friendly_launcher = MissileLauncher(FRIENDLY);
    EXPECT_EQ(friendly_launcher.team(), FRIENDLY);
    MissileLauncher enemy_launcher = MissileLauncher(ENEMY);
    EXPECT_EQ(enemy_launcher.team(), ENEMY);
}

TEST(MissileLauncherTeamTest, check_team_notify_called) {
    InSequence dummy;

    MockProjectileCreatorListener launcher_listener;
    EXPECT_CALL(launcher_listener, notify_projectile_launched(_, FRIENDLY));
    EXPECT_CALL(launcher_listener, notify_projectile_launched(_, ENEMY));

    MissileLauncher friendly_launcher = MissileLauncher(FRIENDLY);
    friendly_launcher.add_listener(&launcher_listener);
    friendly_launcher.create_missile(0, 0, 0, 0);

    MissileLauncher enemy_launcher = MissileLauncher(ENEMY);
    enemy_launcher.add_listener(&launcher_listener);
    enemy_launcher.create_missile(0, 0, 0, 0);
}
