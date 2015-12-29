#pragma once
#include <SDL2/SDL.h>
#include "graphics_handler.h"

class GameObject {

public:
    GameObject(double x_pos, double y_pos) {
        position_.x = x_pos;
        position_.y = y_pos; 
    }

    virtual void update() = 0;
    virtual void draw(GraphicsHandler *graphics) = 0;
    virtual SDL_Point position() { return position_; }

protected:
    SDL_Point position_;
};
 