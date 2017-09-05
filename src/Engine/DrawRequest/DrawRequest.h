#pragma once

#include <SDL2/SDL.h>

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
    explicit DrawRequest(SDL_Texture* texture,
                         SDL_Rect texture_rect,
                         bool is_flyweight,
                         double angle_clockwise_from_vertical,
                         SDL_Point* rotation_point);

    SDL_Texture* texture() const;
    const SDL_Rect& texture_rect() const;
    const bool is_flyweight() const;
    const double angle() const;
    const SDL_Point* rotation_point() const;

private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
    bool is_flyweight_;
    double angle_clockwise_from_vertical_;
    SDL_Point* rotation_point_;
};

