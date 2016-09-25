#pragma once

#include <SDL2/SDL.h>

#include "ship.h"

class BasicEnemy : public Ship {
public:
    BasicEnemy(double x_pos, double y_pos, double x_vel, double y_vel);

    void update();
    void draw(GraphicsHandler *graphics);
    std::vector<Hitbox> get_hitboxes();
    void notify_collision(Ship* collided_ship, int hitbox_number);

    static void set_texture(SDL_Texture* texture);

private:
    static SDL_Texture* missile_texture_;
};
