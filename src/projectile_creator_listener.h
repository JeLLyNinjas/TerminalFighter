#pragma once
#include <string> 

#include "game_constants.h"
#include "observable.h"
#include "missile.h"

class ProjectileCreatorListener {
public: 
    virtual void notify_projectile_launched(Projectile *projectile, Team team) = 0;
};
