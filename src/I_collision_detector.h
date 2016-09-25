#pragma once

#include "game_constants.h"

class GameObject;

class I_CollisionDetector {
public:
    virtual ~I_CollisionDetector() {}
	virtual void add_projectile(Team::Team team, GameObject& projectile) = 0;
	virtual void add_game_object(Team::Team team, GameObject& game_object) = 0;
};
