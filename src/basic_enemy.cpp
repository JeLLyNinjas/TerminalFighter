#include <stdio.h>

#include "basic_enemy.h"

SDL_Texture* BasicEnemy::missile_texture_ = NULL;

BasicEnemy::BasicEnemy(double x_pos, double y_pos, double x_vel, double y_vel)
: Ship(x_pos, y_pos, x_vel, y_vel)
{ }

void BasicEnemy::update() {

}

void BasicEnemy::draw(GraphicsHandler *graphics) {
    if(missile_texture_ == NULL) {
        printf("BasicEnemy graphics were null! Setting BasicEnemy graphic...\n");
        set_texture(graphics->load_image("assets/ships/BasicEnemy.png"));
    }
    graphics->draw(missile_texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::MIDDLE);
}

void BasicEnemy::set_texture(SDL_Texture* texture) {
    missile_texture_ = texture;
}

std::vector<Hitbox> BasicEnemy::get_hitboxes() {
    return std::vector<Hitbox>();
}

void BasicEnemy::notify_collision(Ship* collided_ship, int hitbox_number)
{

}
