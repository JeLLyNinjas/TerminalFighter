#include <glog/logging.h>

#include <SDL2/SDL.h>

#include "GraphicsHandler/I_GraphicsHandler.h"

#include "MainCharacter.h"
#include "MissileLauncher/MissileLauncher.h"

SDL_Texture* MainCharacter::texture_ = NULL;

MainCharacter::MainCharacter(
    double x_pos,
    double y_pos,
    int health,
    std::string graphic_path)
    : GameObject(x_pos, y_pos, 0, 0, health)
    , hitbox_(Hitbox(x_pos_, y_pos_, 100, 100))
    , texture_path_(graphic_path)
    , weapons_() {
}

void MainCharacter::set_texture(SDL_Texture* texture) {
    texture_ = texture;
}

void MainCharacter::add_weapon(std::unique_ptr<GameObject> weapon) {
    weapons_.push_back(std::move(weapon));
}

// GameObject functions

void MainCharacter::update() {
    for (auto& weapon : weapons_) {
        weapon->update();
    }
}

void MainCharacter::draw(I_GraphicsHandler& graphics) {
    if (texture_ == NULL) {
        LOG(WARNING) << "MainCharacter graphics were null! Setting MainCharacter graphic...";
        set_texture(graphics.load_image(texture_path_));
    }

    for (auto& weapon : weapons_) {
        weapon->draw(graphics);
    }

    int w, h;
    SDL_QueryTexture(texture_, NULL, NULL, &w, &h);

    graphics.draw(texture_,
                  graphics.create_sdl_rect(0, 0, w, h),
                  graphics.create_jn_rect(x_pos(), y_pos(), 0.1, 0.1),
                  GraphicPriority::MIDDLE,
                  true,
                  0,
                  NULL);
}


const I_Hitbox& MainCharacter::hitbox() const {
    return hitbox_;
}

void MainCharacter::notify_collision(GameObject& collided_object) {
}

void MainCharacter::take_damage(int damage) {
    health_ -= damage;
    //will not notify_destroy yet while we testing
}
