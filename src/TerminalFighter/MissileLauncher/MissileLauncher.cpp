#include <stdlib.h>

#include "MissileLauncher.h"
#include "Missile/Missile.h"
#include "Util/Util.h"

MissileLauncher::MissileLauncher(
    Team::Team team,
    I_GameObjectMediator& game_object_mediator,
    std::string missile_graphic_path,
    std::string terminal_graphic_path,
    double x_pos, double y_pos)
    : GameObject(x_pos, y_pos, 0, 0, 1)
    , team_(team)
    , game_object_mediator_(game_object_mediator)
    , missile_graphic_path_(missile_graphic_path)
    , terminal_((this->x_pos()) - 400, this->y_pos() - 150, 100, 30, terminal_graphic_path)
    , hitbox_(0, 0, 0, 0) {
    std::unique_ptr<TargetingSystem> temp_targeting_system_ (new TargetingSystem(3, 5, "FFF"));
    targeting_system_ = temp_targeting_system_.get();
    terminal_.Observable<TerminalListener>::add_listener(this);
    game_object_mediator.add_game_object(team_, std::move(temp_targeting_system_));
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
    GameObject* enemy = targeting_system_->get_object(input);

    if (enemy == NULL) {
        return;
    }

    double x_vel = enemy->x_pos() - this->x_pos();
    double y_vel = enemy->y_pos() - this->y_pos();
    float magnitude = x_vel * x_vel + y_vel * y_vel;
    magnitude = 4 * util::inverse_sqrt(magnitude);
    create_missile(this->x_pos(), this->y_pos(),
                   magnitude * x_vel, magnitude * y_vel);
}
