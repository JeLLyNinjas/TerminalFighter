#include <stdlib.h>

#include "GameConstants.h"
#include "MissileLauncher.h"
#include "I_GameObjectMediator.h"
#include "Missile.h"

MissileLauncher::MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator)
    : team_(team)
    , game_object_mediator_(game_object_mediator)
    , terminal_((SCREEN_WIDTH / 2) - 400, SCREEN_HEIGHT - 150, 100, 30)
    , targeting_system_(new TargetingSystem(3, 5, "FFFF"))
    , hitbox_(0, 0, 0, 0) {
    game_object_mediator.add_game_object(team_, std::move(targeting_system_));
}

Team::Team MissileLauncher::team() const {
    return team_;
}

void MissileLauncher::create_missile(double x_pos, double y_pos, double x_vel, double y_vel) {
    std::unique_ptr<Missile> missile(new Missile(x_pos, y_pos, x_vel, y_vel));
    game_object_mediator_.add_projectile(team_, std::move(missile));
}

void MissileLauncher::handle_key_press(const std::string& keypress) {
    terminal_.handle_key_press(keypress);
}

// GameObject

void MissileLauncher::update() {
    if (rand() % 5 == 0) {
        create_missile(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, rand() % 4 - 2, rand() % 4 * -1);
    }

    terminal_.update();
}

void MissileLauncher::draw(I_GraphicsHandler& graphics) {
    terminal_.draw(graphics);
}

const I_Hitbox& MissileLauncher::hitbox() const {
    return hitbox_;
}

void MissileLauncher::notify_collision(GameObject& collided_object) {
    // nothing to do, not a physical object
}

