#pragma once

#include <memory>

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
                SDL_Rect texture_rect,
                GraphicPriority z_level)
    :texture_(texture)
    ,texture_rect_(texture_rect)
    ,z_level_(z_level)
    {}

    SDL_Texture* texture() const {
        return texture_;
    }
    
    const SDL_Rect& texture_rect() const {
        return texture_rect_;
    }
    
    GraphicPriority z_level() const {
        return z_level_;
    }


private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
    GraphicPriority z_level_;
};
