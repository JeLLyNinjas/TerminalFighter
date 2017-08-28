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
                         bool is_flyweight);
    SDL_Texture* texture() const;
    const SDL_Rect& texture_rect() const;
    const bool is_flyweight() const;

private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
    bool is_flyweight_;
};

