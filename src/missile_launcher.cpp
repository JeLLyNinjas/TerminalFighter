#include "missile_launcher.h"

MissileLauncher::MissileLauncher(Team team) 
    : team_(team)
{ }

Missile* MissileLauncher::create_missile(double x_vel, double y_vel, double x_pos, double y_pos) {
    Missile *return_missile = new Missile(x_vel, y_vel, x_pos, y_pos);
    if(team_ == FRIENDLY){
        for (ProjectileCreatorListener * listener : listeners) { 
            listener->notify_friendly_projectile_launched(return_missile);
        }
    }
    else {
        for (ProjectileCreatorListener * listener : listeners) { 
            listener->notify_enemy_projectile_launched(return_missile);
        }
    }
    return  return_missile;
}
