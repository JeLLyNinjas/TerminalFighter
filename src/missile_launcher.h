#pragma once
#include "missile_launcher_listener.h"
#include "observable.h"
#include "missile.h"
#include "game_object.h"
#include <string>

class MissileLauncher : public Observable <MissileLauncherListener> {

public:
    Missile * create_missile(double x_vel, double y_vel, double x_pos, double y_pos);
};
