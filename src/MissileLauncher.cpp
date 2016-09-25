#include "MissileLauncher.h"

#include "I_GameObjectMediator.h"

MissileLauncher::MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator)
    : team_(team)
    , game_object_mediator_(game_object_mediator)
{ }

Team::Team MissileLauncher::team() const {
    return team_;
}

void MissileLauncher::create_missile(double x_pos, double y_pos, double x_vel, double y_vel) {
    std::unique_ptr<Missile> missile(new Missile(x_pos, y_pos, x_vel, y_vel));
    game_object_mediator_.add_projectile(team_, std::move(missile));
}
