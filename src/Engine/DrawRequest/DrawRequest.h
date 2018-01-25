#pragma once

#include <SDL2/SDL.h>
#include "JN_Rect/JN_Rect.h"

enum GraphicPriority {
    OVERLAY,
    UI,
    FRONT,
    MIDDLE,
    BACK,
    BACKGROUND
};

class DrawRequest {
public:
    //clock_angle is the angle in degrees, clockwise from the y-axis
    explicit DrawRequest(SDL_Texture* texture,
                         SDL_Rect src_rect,
                         JN_Rect dest_rect,
                         bool cleanup,
                         double clock_angle,
                         SDL_Point* rotation_point);

    SDL_Texture* texture() const;
    const SDL_Rect& dest_rect(int screen_width, int screen_height);
    const SDL_Rect& src_rect();
    const bool cleanup() const;
    const double angle() const;
    const SDL_Point* rotation_point() const;

private:

    SDL_Texture* texture_;
    JN_Rect dest_rect_;
    SDL_Rect sdl_src_rect_;
    SDL_Rect sdl_dest_rect_;
    bool cleanup_;
    double angle_clockwise_from_vertical_;
    SDL_Point* rotation_point_;
};

