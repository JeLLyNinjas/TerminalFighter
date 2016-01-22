#include "missile_launcher.h"

MissileLauncher::MissileLauncher(Team team) 
    : team_(team)
{ }

const Team& MissileLauncher::team() const {
    return team_;
}

Missile* MissileLauncher::create_missile(double x_pos, double y_pos, double x_vel, double y_vel){
    Missile *return_missile = new Missile(x_pos, y_pos, x_vel, y_vel);
    for (ProjectileCreatorListener * listener : listeners) { 
        listener->notify_projectile_launched(return_missile, team_);
    }
    return  return_missile;
}
