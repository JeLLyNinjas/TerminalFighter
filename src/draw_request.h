#pragma once

<<<<<<< HEAD
#include <SDL2/SDL.h>

=======
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

>>>>>>> a948aa3... first attempt at graphics layering
class DrawRequest {

public:
    explicit DrawRequest(SDL_Texture *texture,
<<<<<<< HEAD
                SDL_Rect texture_rect)
    :texture_(texture)
    ,texture_rect_(texture_rect)
=======
                SDL_Rect texture_rect,
                GraphicPriority z_level)
    :texture_(texture)
    ,texture_rect_(texture_rect)
    ,z_level_(z_level)
>>>>>>> a948aa3... first attempt at graphics layering
    {}

    SDL_Texture* texture() const {
        return texture_;
    }
    
    const SDL_Rect& texture_rect() const {
        return texture_rect_;
    }
<<<<<<< HEAD
=======
    
    GraphicPriority z_level() const {
        return z_level_;
    }

>>>>>>> a948aa3... first attempt at graphics layering

private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
<<<<<<< HEAD
=======
    GraphicPriority z_level_;
>>>>>>> a948aa3... first attempt at graphics layering
};
