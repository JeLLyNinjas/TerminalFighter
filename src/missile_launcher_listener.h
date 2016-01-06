#pragma once
#include <string> 

#include "observable.h"
#include "missile.h"

class MissileLauncherListener {
public: 
    virtual void notify_missile_launched(Missile *missile) = 0;
};
