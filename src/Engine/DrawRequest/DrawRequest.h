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
                         JN_Rect src_rect,
                         JN_Rect dest_rect,
                         bool cleanup,
                         double clock_angle,
                         SDL_Point* rotation_point);

    SDL_Texture* texture() const;
    const SDL_Rect& dest_rect(int screen_width, int screen_height);
    const SDL_Rect& src_rect(int screen_width, int screen_height);
    const bool cleanup() const;
    const double angle() const;
    const SDL_Point* rotation_point() const;

private:
    
    // Converts the JN_Rect into the private member SDL_Rect, and then returns the
    // private SDL_Rect member.
    const SDL_Rect& return_sdl_rect(SDL_Rect& sdl_rect, JN_Rect&, 
            int screen_width, int screen_height);

    SDL_Texture* texture_;
    JN_Rect src_rect_;
    JN_Rect dest_rect_;
    SDL_Rect sdl_src_rect_;
    SDL_Rect sdl_dest_rect_;
    bool cleanup_;
    double angle_clockwise_from_vertical_;
    SDL_Point* rotation_point_;
};

