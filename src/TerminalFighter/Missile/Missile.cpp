#include <stdio.h>

#include <SDL2/SDL.h>

#include "../Engine/GraphicsHandler/I_GraphicsHandler.h"

#include "Missile.h"

SDL_Texture* Missile::missile_texture_ = NULL;

Missile::Missile(double x_pos, double y_pos, double x_vel, double y_vel, int health)
    : GameObject(x_pos, y_pos, x_vel, y_vel, health)
    , hitbox_(Hitbox(x_pos, y_pos, 10, 50)) {
}

Missile::~Missile() {
    std::printf("Missile Died \n");
}

void Missile::update() {
    x_pos_ += x_vel_;
    y_pos_ += y_vel_;
    hitbox_.set_pos(x_pos_, y_pos_);
}

void Missile::draw(I_GraphicsHandler& graphics) {
    if (missile_texture_ == NULL) {
        printf("Missile graphics were null! Setting missile graphic...\n");
        set_texture(graphics.load_image("assets/projectiles/missile.png"));
    }

    graphics.draw(missile_texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::MIDDLE);
}

const I_Hitbox& Missile::hitbox() const {
    return hitbox_;
}

void Missile::notify_collision(GameObject& collided_object) {
    collided_object.take_damage(5); //some made up numbers. Maybe these should be part of an INI file that we can easily edit later
    notify_destroyed();
}

void Missile::set_texture(SDL_Texture* texture) {
    missile_texture_ = texture;
}

