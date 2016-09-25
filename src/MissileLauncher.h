#pragma once
#include <string>

#include "GameObject.h"
#include "Missile.h"
#include "Observable.h"
#include "GameConstants.h"

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
