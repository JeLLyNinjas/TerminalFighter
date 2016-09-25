#include "GameObjectMediator.h"

#include "I_CollisionDetector.h"
#include "I_Universe.h"

GameObjectMediator::GameObjectMediator(I_Universe& universe, I_CollisionDetector& collision_detector)
: universe_(universe)
, collision_detector_(collision_detector)
{}

void GameObjectMediator::add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object)
{
	universe_.add_game_object(std::move(game_object));
	collision_detector_.add_game_object(team, *game_object);
}

void GameObjectMediator::add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile)
{
	universe_.add_game_object(std::move(projectile));
	collision_detector_.add_projectile(team, *projectile);
}
