#pragma once
#include "missile_launcher_listener.h"
#include "observable.h"
#include "missile.h"
#include <string>

class MissileLauncher : public Observable <MissileLauncherListener> {

public:
    Missile * create_missile(std::string name);
};
