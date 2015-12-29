#include "missile.h"
#include <stdio.h>

SDL_Texture* Missile::missile_texture_ = NULL;

Missile::Missile(double x_vel, double y_vel, double x_pos, double y_pos) 
: Projectile(x_pos, y_pos, x_vel, y_vel) 
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
    graphics->draw(missile_texture_, (int)x_pos(), (int)y_pos());
}

void Missile::set_texture(SDL_Texture* texture) {
    missile_texture_ = texture;
}
