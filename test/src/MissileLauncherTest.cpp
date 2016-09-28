#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "GameConstants.h"
#include "MissileLauncher.h"
#include "Missile.h"
#include "mocks/MockGameObjectMediator.h"

using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class MissileLauncherTest : public ::testing::Test {
protected:
    std::unique_ptr<MissileLauncher> launcher_;
    MockGameObjectMediator mediator_;

    virtual void SetUp() {
        launcher_ = std::unique_ptr<MissileLauncher>(new MissileLauncher(Team::FRIENDLY, mediator_));
    }

    virtual void TearDown() {}
};

TEST_F(MissileLauncherTest, team_set) {
    MissileLauncher friendly_launcher = MissileLauncher(Team::FRIENDLY, mediator_);
    EXPECT_EQ(friendly_launcher.team(), Team::FRIENDLY);
    MissileLauncher enemy_launcher = MissileLauncher(Team::ENEMY, mediator_);
    EXPECT_EQ(enemy_launcher.team(), Team::ENEMY);
}

TEST_F(MissileLauncherTest, multiple_missiles) {
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::FRIENDLY, _))
    .Times(3);
    launcher_->create_missile(0, 0, 0, 0);
    launcher_->create_missile(0, 0, 0, 0);
    launcher_->create_missile(0, 0, 0, 0);
}

TEST_F(MissileLauncherTest, correct_params_passed) {
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::FRIENDLY, AllOf(Property(&Missile::x_pos, 11.0),
                Property(&Missile::y_pos, 12.0),
                Property(&Missile::x_vel, 13.0),
                Property(&Missile::y_vel, 14.0))));
    launcher_->create_missile(11, 12, 13, 14);
}

TEST_F(MissileLauncherTest, correct_missiles_passed) {
    InSequence dummy;
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::FRIENDLY, AllOf(Property(&Missile::x_pos, 10.0),
                Property(&Missile::y_pos, 10.0),
                Property(&Missile::x_vel, 10.0),
                Property(&Missile::y_vel, 10.0))));
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::FRIENDLY, AllOf(Property(&Missile::x_pos, 20.0),
                Property(&Missile::y_pos, 20.0),
                Property(&Missile::x_vel, 20.0),
                Property(&Missile::y_vel, 20.0))));
    launcher_->create_missile(10, 10, 10, 10);
    launcher_->create_missile(20, 20, 20, 20);
}

TEST_F(MissileLauncherTest, check_missiles_correct_team) {
    InSequence dummy;
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::FRIENDLY, _));
    EXPECT_CALL(mediator_, add_projectile_proxy(Team::ENEMY, _));
    MissileLauncher friendly_launcher = MissileLauncher(Team::FRIENDLY, mediator_);
    friendly_launcher.create_missile(0, 0, 0, 0);
    MissileLauncher enemy_launcher = MissileLauncher(Team::ENEMY, mediator_);
    enemy_launcher.create_missile(0, 0, 0, 0);
}
