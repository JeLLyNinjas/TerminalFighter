#include "GameConstants.h"
#include "CollisionDetector.h"
#include "Hitbox.h"

CollisionDetector::CollisionDetector() {
}

CollisionDetector::~CollisionDetector() {
}

void CollisionDetector::add_projectile(Team::Team team, GameObject& projectile) {
    projectiles_.push_back(&projectile);
    affiliation_[projectile.id()] = team;
}

void CollisionDetector::add_game_object(Team::Team team, GameObject& game_object) {
    non_projectiles_.push_back(&game_object);
    affiliation_[game_object.id()] = team;
}

// Do not check collisions between projectiles and projectiles
// TODO check collisions based on teams
void CollisionDetector::check_collisions() {
    for (auto a : projectiles_) {
        for (auto b : non_projectiles_) {
            if (affiliation_[a->id()] == affiliation_[b->id()]) {
                continue;
            }

            if (a->hitbox().is_overlapping(b->hitbox())) {
                a->notify_collision(*b);
                b->notify_collision(*a);
            }
        }
    }

    for (auto& a : non_projectiles_) {
        for (auto& b : non_projectiles_) {
            if (affiliation_[a->id()] == affiliation_[b->id()]) {
                continue;
            }

            if (a->hitbox().is_overlapping(b->hitbox()) && a->id() != b->id()) {
                a->notify_collision(*b);
            }
        }
    }
}

void CollisionDetector::update() {
    check_collisions();
}

void CollisionDetector::object_destroyed(int id) {
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
