#include <glog/logging.h>
#include <SDL2/SDL.h>

#include "GraphicsHandler/I_GraphicsHandler.h"

#include "BasicEnemy.h"

SDL_Texture* BasicEnemy::texture_ = NULL;

BasicEnemy::BasicEnemy(
    double x_pos, double y_pos,
    double x_vel, double y_vel,
    int health,
    std::string graphic_path)
    : GameObject(x_pos, y_pos, x_vel, y_vel, health)
    , hitbox_(Hitbox(x_pos_, y_pos_, 90, 50))
    , texture_path_(graphic_path) {
}

BasicEnemy::~BasicEnemy() {
}

void BasicEnemy::update() {
    hitbox_.set_pos(x_pos_, y_pos_);
}

void BasicEnemy::draw(I_GraphicsHandler& graphics) {
    if (texture_ == NULL) {
        LOG(WARNING) << "BasicEnemy graphics were null! Setting BasicEnemy graphic...";
        set_texture(graphics.load_image("assets/images/ships/BasicEnemy.png"));
    }
    SDL_Rect src_rect;
    SDL_QueryTexture(texture_, NULL, NULL, &src_rect.w, &src_rect.h);
    src_rect.x = 0;
    src_rect.y = 0;

    graphics.draw(texture_,
                  src_rect,
                  (int)x_pos(),
                  (int)y_pos(),
                  GraphicPriority::MIDDLE,
                  true,
                  0,
                  NULL);
}

void BasicEnemy::set_texture(SDL_Texture* texture) {
    texture_ = texture;
}

const I_Hitbox& BasicEnemy::hitbox() const {
    return hitbox_;
}

void BasicEnemy::notify_collision(GameObject& collided_object) {
    collided_object.take_damage(5);
}
