#pragma once
#include <string> 

#include "observable.h"
#include "missile.h"

class ProjectileCreatorListener {
public: 
    virtual void notify_friendly_projectile_launched(Projectile *projectile) = 0;
    virtual void notify_enemy_projectile_launched(Projectile *projectile) = 0;
};
