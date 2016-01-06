#pragma once
#include <string>

#include "game_object.h"
#include "missile.h"
#include "missile_launcher_listener.h"
#include "observable.h"

class MissileLauncher : public Observable <MissileLauncherListener> {
public:
    Missile * create_missile(double x_vel, double y_vel, double x_pos, double y_pos);
};
