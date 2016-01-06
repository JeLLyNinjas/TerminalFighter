#pragma once
#include <string> 

#include "observable.h"
#include "missile.h"

class ProjectileCreatorListener {
public: 
    virtual void notify_projectile_launched(Projectile *projectile) = 0;
};
