#pragma once
#include <vector>

#include "I_collision_detector.h"

class GameObject;

class CollisionDetector : public I_CollisionDetector {
public:
    CollisionDetector();
    ~CollisionDetector();

    void add_game_object(Team::Team team, GameObject& game_object);
    void add_projectile(Team::Team team, GameObject& projectile);
    void check_collisions();

private:
    std::vector<GameObject*> non_projectiles_;
    std::vector<GameObject*> projectiles_;
};
