#pragma once
#include <string>

#include "game_object.h"
#include "missile.h"
#include "projectile_creator_listener.h"
#include "observable.h"

class MissileLauncher : public Observable <ProjectileCreatorListener> {
public:
    Missile * create_missile(double x_vel, double y_vel, double x_pos, double y_pos);
};
