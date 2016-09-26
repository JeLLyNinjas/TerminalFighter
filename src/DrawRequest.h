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
    explicit DrawRequest(SDL_Texture *texture,
                         SDL_Rect texture_rect);
    SDL_Texture* texture() const;
    const SDL_Rect& texture_rect() const;

private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
};
