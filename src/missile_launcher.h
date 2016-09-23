#pragma once
#include <string>

#include "game_object.h"
#include "missile.h"
#include "projectile_creator_listener.h"
#include "observable.h"
#include "game_constants.h"

class I_GameObjectMediator;

class MissileLauncher {
public:
	MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator);
	Team::Team team() const;
	void create_missile(double x_vel, double y_vel, double x_pos, double y_pos);

private:
	Team::Team team_;
	I_GameObjectMediator& game_object_mediator_;
};
