#pragma once
#include <string>
#include "game_object.h"
#include <SDL2/SDL.h>

class Missile : public Game_Object {
public:
    Missile(double x_vel, double y_vel, double x_pos, double y_pos);

    void update();
    SDL_Texture *graphic_update();
    static void set_texture(SDL_Texture* texture);

    double return_x_velocity();
    double return_y_velocity();
    double return_x_position();
    double return_y_position();

private:
    static SDL_Texture* missile_texture_;
};

