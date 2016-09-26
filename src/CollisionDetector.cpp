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
    for(auto projectile : projectiles_)
    {
        projectile->hitbox();
    }

    for(auto &non_projectile : non_projectiles_)
    {
        non_projectile->hitbox();
    }
}

void CollisionDetector::update()
{

}

void CollisionDetector::object_destroyed(int id)
{
    for (int i = 0; i < projectiles_.size(); i++) {
        if (projectiles_[i]->id() == id) {
            projectiles_.erase(projectiles_.begin() + i);
            return;
        }
    }

    for (int i = 0; i < non_projectiles_.size(); i++) {
        if (non_projectiles_[i]->id() == id) {
            non_projectiles_.erase(non_projectiles_.begin() + i);
            return;
        }
    }

    SDL_assert(true && "Object to be deleted not found in CollisionDetector object vectors"); // object to be destroyed not found
}
