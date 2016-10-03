#include <stdio.h>

#include "BasicEnemy.h"
#include "GraphicsHandler.h"

SDL_Texture* BasicEnemy::texture_ = NULL;

BasicEnemy::BasicEnemy(double x_pos, double y_pos, double x_vel, double y_vel)
    : GameObject(x_pos, y_pos, x_vel, y_vel)
    , hitbox_(Hitbox(x_pos_, y_pos_, 100, 100)) {
}

void BasicEnemy::update() {
    hitbox_.set_pos(x_pos_, y_pos_);
}

void BasicEnemy::draw(GraphicsHandler& graphics) {
    if (texture_ == NULL) {
        printf("BasicEnemy graphics were null! Setting BasicEnemy graphic...\n");
        set_texture(graphics.load_image("assets/ships/BasicEnemy.png"));
    }

    graphics.draw(texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::MIDDLE);
}

void BasicEnemy::set_texture(SDL_Texture* texture) {
    texture_ = texture;
}

const I_Hitbox& BasicEnemy::hitbox() const {
    return hitbox_;
}

void BasicEnemy::notify_collision(GameObject& collided_object) {
    notify_destroyed();
}
