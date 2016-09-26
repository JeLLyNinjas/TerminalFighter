#pragma once

#include "GameObject.h"

#include "I_Updatable.h"

class GameObject;

class I_CollisionDetector : public I_Updatable {
public:
    virtual ~I_CollisionDetector() {}
    virtual void add_game_object(Team::Team team, GameObject& game_object) = 0;
    virtual void add_projectile(Team::Team team, GameObject& projectile) = 0;
    virtual void check_collisions() = 0;
    virtual void update() = 0;
};
