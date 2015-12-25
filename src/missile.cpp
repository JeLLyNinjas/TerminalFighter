#include "missile.h"

SDL_Texture* Missile::missile_texture_ = NULL;

Missile::Missile(double x_vel, double y_vel, double x_pos, double y_pos) 
: Game_Object(x_vel, y_vel, x_pos, y_pos) {

}

void Missile::update() {
    x_position_ += x_velocity_;
    y_position_ += y_velocity_; 
}

void Missile::draw(GraphicsHandler *graphics) {
    printf("Got called to draw!\n");
    graphics->draw(missile_texture_, (int)return_x_position(), (int)return_y_position());
}

double Missile::return_x_velocity() {
    return x_velocity_;
}
double Missile::return_y_velocity() {
    return y_velocity_;
}
double Missile::return_x_position() { 
    return x_position_;
}
double Missile::return_y_position() {
    return y_position_;
}

void Missile::set_texture(SDL_Texture* texture) {
    missile_texture_ = texture;
}
