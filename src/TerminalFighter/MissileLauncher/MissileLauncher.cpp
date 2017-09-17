#include <stdlib.h>

#include "MissileLauncher.h"
#include "Missile/Missile.h"
#include "Util/Util.h"

MissileLauncher::MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator)
    : team_(team)
    , game_object_mediator_(game_object_mediator)
    , terminal_((SCREEN_WIDTH / 2) - 400, SCREEN_HEIGHT - 150, 100, 30)
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

void MissileLauncher::play(I_AudioHandler& audio) {
    audio.play_chunk(audio.load_chunk("assets/sounds/NFF-laser-gun-03.wav"));
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

    double x_vel = enemy->x_pos() - (SCREEN_WIDTH / 2);
    double y_vel = enemy->y_pos() - (SCREEN_HEIGHT - 10);
    float magnitude = x_vel * x_vel + y_vel * y_vel;
    magnitude = 4 * util::inverse_sqrt(magnitude);
    create_missile(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10,
                   magnitude * x_vel, magnitude * y_vel);
}
