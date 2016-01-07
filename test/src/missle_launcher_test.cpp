#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_constants.h"
#include "missile_launcher.h"
#include "mocks/mock_projectile_creator_listener.h"

using ::testing::_;
using ::testing::InSequence;

class MissileLauncherTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST(MissileLauncherTest, team_set) {
    MissileLauncher friendly_launcher = MissileLauncher(FRIENDLY);
    friendly_launcher.team() == FRIENDLY;
    MissileLauncher enemy_launcher = MissileLauncher(ENEMY);
    enemy_launcher.team() == ENEMY;
}

TEST(MissileLauncherTest, check_listeners_notified_onlaunch) {
    MockProjectileCreatorListener launcher_listener;
    EXPECT_CALL(launcher_listener, notify_friendly_projectile_launched(_))
        .Times(1);

    MissileLauncher launcher = MissileLauncher(FRIENDLY);
    launcher.add_listener(&launcher_listener);
    launcher.create_missile(0, 0, 0, 0);
}

TEST(MissileLauncherTest, check_team_notify_called) {
    InSequence dummy;

    MockProjectileCreatorListener launcher_listener;
    EXPECT_CALL(launcher_listener, notify_friendly_projectile_launched(_));
    EXPECT_CALL(launcher_listener, notify_enemy_projectile_launched(_));

    MissileLauncher friendly_launcher = MissileLauncher(FRIENDLY);
    friendly_launcher.add_listener(&launcher_listener);
    friendly_launcher.create_missile(0, 0, 0, 0);

    MissileLauncher enemy_launcher = MissileLauncher(ENEMY);
    enemy_launcher.add_listener(&launcher_listener);
    enemy_launcher.create_missile(0, 0, 0, 0);
}