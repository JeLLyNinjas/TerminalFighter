#pragma once

#include <memory>

#include "game_constants.h"
#include "game_object.h"
#include "projectile.h"

class I_GameObjectMediator {
public:
	virtual void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object) = 0;
	virtual void add_projectile(Team::Team team, std::unique_ptr<Projectile> projectile) = 0;
};
