#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <SDL.h>

#include "../src/Engine/Team.h"
#include "../src/Engine/CollisionDetector.h"
#include "mocks/MockGameObject.h"
#include "mocks/MockHitbox.h"

using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;
using ::testing::Ref;

class CollisionDetectorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(CollisionDetectorTest, gameobject_gameobject_collision) {
    CollisionDetector detector;
    MockGameObject gameobj_1;
    MockHitbox hitbox_1;
    MockGameObject gameobj_2;
    MockHitbox hitbox_2;
    ON_CALL(gameobj_1, hitbox()).WillByDefault(ReturnRef(hitbox_1));
    ON_CALL(hitbox_1, is_overlapping(Ref(hitbox_2))).WillByDefault(Return(true));
    ON_CALL(gameobj_2, hitbox()).WillByDefault(ReturnRef(hitbox_2));
    ON_CALL(hitbox_2, is_overlapping(Ref(hitbox_1))).WillByDefault(Return(true));
    EXPECT_CALL(gameobj_1, notify_collision(Ref(gameobj_2)));
    EXPECT_CALL(gameobj_2, notify_collision(Ref(gameobj_1)));
    detector.add_game_object(Team::FRIENDLY, gameobj_1);
    detector.add_game_object(Team::ENEMY, gameobj_2);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, gameobject_gameobject_no_collision) {
    CollisionDetector detector;
    MockGameObject gameobj_1;
    MockHitbox hitbox_1;
    MockGameObject gameobj_2;
    MockHitbox hitbox_2;
    ON_CALL(gameobj_1, hitbox()).WillByDefault(ReturnRef(hitbox_1));
    ON_CALL(hitbox_1, is_overlapping(Ref(hitbox_2))).WillByDefault(Return(false));
    ON_CALL(gameobj_2, hitbox()).WillByDefault(ReturnRef(hitbox_2));
    ON_CALL(hitbox_2, is_overlapping(Ref(hitbox_1))).WillByDefault(Return(false));
    EXPECT_CALL(gameobj_1, notify_collision(Ref(gameobj_2))).Times(0);
    EXPECT_CALL(gameobj_2, notify_collision(Ref(gameobj_1))).Times(0);
    detector.add_game_object(Team::FRIENDLY, gameobj_1);
    detector.add_game_object(Team::ENEMY, gameobj_2);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, projectile_gameobject_collision) {
    CollisionDetector detector;
    MockGameObject projectile;
    MockHitbox proj_hitbox;
    MockGameObject gameobj;
    MockHitbox gameobj_hitbox;
    ON_CALL(projectile, hitbox()).WillByDefault(ReturnRef(proj_hitbox));
    ON_CALL(proj_hitbox, is_overlapping(Ref(gameobj_hitbox))).WillByDefault(Return(true));
    ON_CALL(gameobj, hitbox()).WillByDefault(ReturnRef(gameobj_hitbox));
    ON_CALL(gameobj_hitbox, is_overlapping(Ref(proj_hitbox))).WillByDefault(Return(true));
    EXPECT_CALL(projectile, notify_collision(Ref(gameobj)));
    EXPECT_CALL(gameobj, notify_collision(Ref(projectile)));
    detector.add_projectile(Team::FRIENDLY, projectile);
    detector.add_game_object(Team::ENEMY, gameobj);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, projectile_gameobject_no_collision) {
    CollisionDetector detector;
    MockGameObject projectile;
    MockHitbox proj_hitbox;
    MockGameObject gameobj;
    MockHitbox gameobj_hitbox;
    ON_CALL(projectile, hitbox()).WillByDefault(ReturnRef(proj_hitbox));
    ON_CALL(proj_hitbox, is_overlapping(Ref(gameobj_hitbox))).WillByDefault(Return(false));
    ON_CALL(gameobj, hitbox()).WillByDefault(ReturnRef(gameobj_hitbox));
    ON_CALL(gameobj_hitbox, is_overlapping(Ref(proj_hitbox))).WillByDefault(Return(false));
    EXPECT_CALL(projectile, notify_collision(Ref(gameobj))).Times(0);
    EXPECT_CALL(gameobj, notify_collision(Ref(projectile))).Times(0);
    detector.add_projectile(Team::FRIENDLY, projectile);
    detector.add_game_object(Team::ENEMY, gameobj);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, projectile_projectile) {
    CollisionDetector detector;
    MockGameObject proj_1;
    MockHitbox proj_1_hitbox;
    MockGameObject proj_2;
    MockHitbox proj_2_hitbox;
    ON_CALL(proj_1, hitbox()).WillByDefault(ReturnRef(proj_1_hitbox));
    ON_CALL(proj_1_hitbox, is_overlapping(Ref(proj_2_hitbox))).WillByDefault(Return(true));
    ON_CALL(proj_2, hitbox()).WillByDefault(ReturnRef(proj_2_hitbox));
    ON_CALL(proj_2_hitbox, is_overlapping(Ref(proj_1_hitbox))).WillByDefault(Return(true));
    EXPECT_CALL(proj_1, notify_collision(Ref(proj_2))).Times(0);
    EXPECT_CALL(proj_2, notify_collision(Ref(proj_1))).Times(0);
    detector.add_projectile(Team::FRIENDLY, proj_1);
    detector.add_projectile(Team::ENEMY, proj_2);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, gameobject_gameobject_same_team) {
    CollisionDetector detector;
    MockGameObject gameobj_1;
    MockHitbox hitbox_1;
    MockGameObject gameobj_2;
    MockHitbox hitbox_2;
    ON_CALL(gameobj_1, hitbox()).WillByDefault(ReturnRef(hitbox_1));
    ON_CALL(hitbox_1, is_overlapping(Ref(hitbox_2))).WillByDefault(Return(true));
    ON_CALL(gameobj_2, hitbox()).WillByDefault(ReturnRef(hitbox_2));
    ON_CALL(hitbox_2, is_overlapping(Ref(hitbox_1))).WillByDefault(Return(true));
    EXPECT_CALL(gameobj_1, notify_collision(Ref(gameobj_2))).Times(0);
    EXPECT_CALL(gameobj_2, notify_collision(Ref(gameobj_1))).Times(0);
    detector.add_game_object(Team::FRIENDLY, gameobj_1);
    detector.add_game_object(Team::FRIENDLY, gameobj_2);
    detector.check_collisions();
}

TEST_F(CollisionDetectorTest, projectile_gameobject_same_team) {
    CollisionDetector detector;
    MockGameObject projectile;
    MockHitbox proj_hitbox;
    MockGameObject gameobj;
    MockHitbox gameobj_hitbox;
    ON_CALL(projectile, hitbox()).WillByDefault(ReturnRef(proj_hitbox));
    ON_CALL(proj_hitbox, is_overlapping(Ref(gameobj_hitbox))).WillByDefault(Return(true));
    ON_CALL(gameobj, hitbox()).WillByDefault(ReturnRef(gameobj_hitbox));
    ON_CALL(gameobj_hitbox, is_overlapping(Ref(proj_hitbox))).WillByDefault(Return(true));
    EXPECT_CALL(projectile, notify_collision(Ref(gameobj))).Times(0);
    EXPECT_CALL(gameobj, notify_collision(Ref(projectile))).Times(0);
    detector.add_projectile(Team::FRIENDLY, projectile);
    detector.add_game_object(Team::FRIENDLY, gameobj);
    detector.check_collisions();
}
