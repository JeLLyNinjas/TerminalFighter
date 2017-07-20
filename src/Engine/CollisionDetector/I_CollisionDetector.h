#pragma once

#include "GameObject/GameObject.h"
#include "GameObject/I_Updatable.h"
#include "DestroyedListener.h"
#include "Team/Team.h"

class GameObject;

class I_CollisionDetector : public I_Updatable, public DestroyedListener {
public:
    virtual ~I_CollisionDetector() {}
    virtual void add_game_object(Team::Team team, GameObject& game_object) = 0;
    virtual void add_projectile(Team::Team team, GameObject& projectile) = 0;
    virtual void check_collisions() = 0;
    virtual void update() = 0;
    virtual void object_destroyed(int id) = 0;
};
