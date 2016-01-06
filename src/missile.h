#pragma once
#include "projectile.h"
#include <SDL2/SDL.h>

class Missile : public Projectile {
public:
    Missile(double x_pos, double y_pos, double x_vel, double y_vel);

    void update();
    void draw(GraphicsHandler *graphics);
    std::vector<Hitbox> get_hitboxes();
    
    static void set_texture(SDL_Texture* texture);

private:
    static SDL_Texture* missile_texture_;
};

