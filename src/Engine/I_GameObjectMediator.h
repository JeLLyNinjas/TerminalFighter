#pragma once

#include <memory>

#include "Team.h"
#include "GameObject.h"

class I_GameObjectMediator {
public:
    virtual ~I_GameObjectMediator() {}
    virtual void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object) = 0;
    virtual void add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile) = 0;
};
