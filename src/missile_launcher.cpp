#include "missile_launcher.h"

Missile * MissileLauncher::create_missile(double x_vel, double y_vel, double x_pos, double y_pos) {
    Missile *return_missile = new Missile(x_vel, y_vel, x_pos, y_pos);
    for (ProjectileCreatorListener * listener : listeners) { 
        listener->notify_projectile_launched(return_missile);
    }
    return  return_missile;
}
