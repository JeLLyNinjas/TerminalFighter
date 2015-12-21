#pragma once
#include "observable.h"
#include "missile.h"
#include <string> 

class MissileLauncherListener {

public: 
    virtual void notify_missile_launched(Missile *missile) = 0;

};
