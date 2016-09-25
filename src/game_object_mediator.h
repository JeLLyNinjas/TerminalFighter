#pragma once

#include "I_game_object_mediator.h"

class I_Universe;
class I_CollisionDetector;

class GameObjectMediator : public I_GameObjectMediator {
    
public:
    GameObjectMediator(I_Universe& universe, I_CollisionDetector& collision_detector);
	void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object);
	void add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile);

private:
    I_Universe& universe_;
    I_CollisionDetector& collision_detector_;
};
