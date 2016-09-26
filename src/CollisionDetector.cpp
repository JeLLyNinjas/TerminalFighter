#include "GameConstants.h"
#include "CollisionDetector.h"
#include "Hitbox.h"

CollisionDetector::CollisionDetector()
{

}


CollisionDetector::~CollisionDetector()
{

}

void CollisionDetector::add_projectile(Team::Team team, GameObject& projectile)
{
    projectiles_.push_back(&projectile);
}

void CollisionDetector::add_game_object(Team::Team team, GameObject& game_object)
{
    non_projectiles_.push_back(&game_object);
}

void CollisionDetector::check_collisions()
{

}

void CollisionDetector::update()
{

}
