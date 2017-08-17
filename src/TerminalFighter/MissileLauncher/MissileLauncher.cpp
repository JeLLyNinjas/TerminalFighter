#include <stdlib.h>

#include "MissileLauncher.h"
#include "Missile/Missile.h"

MissileLauncher::MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator)
    : team_(team)
    , game_object_mediator_(game_object_mediator)
    , terminal_((SCREEN_WIDTH / 2) - 400, SCREEN_HEIGHT - 150, 100, 30)
    , targeting_system_(new TargetingSystem(3, 5, "FFF"))
    , hitbox_(0, 0, 0, 0) {
    terminal_.Observable<TerminalListener>::add_listener(this);
    game_object_mediator.add_game_object(team_, targeting_system_.unique_ptr);
}

Team::Team MissileLauncher::team() const {
    return team_;
}

void MissileLauncher::create_missile(double x_pos, double y_pos, double x_vel, double y_vel) {
    std::unique_ptr<Missile> missile(new Missile(x_pos, y_pos, x_vel, y_vel, 5));
    game_object_mediator_.add_projectile(team_, std::move(missile));
}

void MissileLauncher::handle_key_press(const std::string& keypress) {
    terminal_.handle_key_press(keypress);
}

// GameObject

void MissileLauncher::update() {
    if (rand() % 5 == 0) {
        //create_missile(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, rand() % 4 - 2, rand() % 4 * -1);
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

void MissileLauncher::handle_input(const std::string& input) {
    printf("GOT SOME WORD?\n");
    //GameObject& enemy = targeting_system_->get_object(input);
    GameObject& enemy = targeting_system_->get_object(input);
    printf("GOT SOME ENEMY?\n");
    //create_missile(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100,
    //enemy.x_pos() - (SCREEN_WIDTH / 2), enemy.y_pos() - (SCREEN_HEIGHT / 2));
}
