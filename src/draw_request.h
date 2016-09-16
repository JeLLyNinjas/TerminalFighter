#pragma once

<<<<<<< HEAD
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
=======
#include <SDL2/SDL.h>

>>>>>>> 6e2c05a... reposnd to pr
class DrawRequest {

public:
    explicit DrawRequest(SDL_Texture *texture,
<<<<<<< HEAD
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
=======
                SDL_Rect texture_rect)
    :texture_(texture)
    ,texture_rect_(texture_rect)
>>>>>>> 6e2c05a... reposnd to pr
    {}

    SDL_Texture* texture() const {
        return texture_;
    }
    
    const SDL_Rect& texture_rect() const {
        return texture_rect_;
    }
<<<<<<< HEAD
<<<<<<< HEAD
=======
    
    GraphicPriority z_level() const {
        return z_level_;
    }

>>>>>>> a948aa3... first attempt at graphics layering
=======
>>>>>>> 6e2c05a... reposnd to pr

private:
    SDL_Texture* texture_;
    SDL_Rect texture_rect_;
<<<<<<< HEAD
<<<<<<< HEAD
=======
    GraphicPriority z_level_;
>>>>>>> a948aa3... first attempt at graphics layering
=======
>>>>>>> 6e2c05a... reposnd to pr
};
