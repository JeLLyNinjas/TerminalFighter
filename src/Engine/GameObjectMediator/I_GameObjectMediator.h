#pragma once

#include <memory>
#include <string>

#include "Team/Team.h"
#include "GameObject/GameObject.h"

class I_GameObjectMediator {
public:
    virtual ~I_GameObjectMediator() {}
    virtual void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object) = 0;
    virtual void add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile) = 0;
    virtual void play_sound(std::string path) = 0;
};
