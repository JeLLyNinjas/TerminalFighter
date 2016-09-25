#include <stdio.h>

#include "Missile.h"
#include "GraphicsHandler.h"

SDL_Texture* Missile::missile_texture_ = NULL;

Missile::Missile(double x_pos, double y_pos, double x_vel, double y_vel)
: GameObject(x_pos, y_pos, x_vel, y_vel)
, hitbox_(Hitbox(x_pos, y_pos, 10, 50))
{ }

void Missile::update() {
    x_pos_ += x_vel_;
    y_pos_ += y_vel_;
}

void Missile::draw(GraphicsHandler *graphics) {
    if(missile_texture_ == NULL) {
        printf("Missile graphics were null! Setting missile graphic...\n");
        set_texture(graphics->load_image("assets/projectiles/missile.png"));
    }
    graphics->draw(missile_texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::MIDDLE);
}

const Hitbox& Missile::hitbox() const {
    return hitbox_;
}

void Missile::notify_collision(GameObject* collided_object)
{

}

void Missile::set_texture(SDL_Texture* texture) {
    missile_texture_ = texture;
}

