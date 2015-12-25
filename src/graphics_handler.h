#pragma once

#include <SDL2/SDL.h>

class GraphicsHandler {

public:
    GraphicsHandler(SDL_Renderer *renderer);
    void draw(SDL_Texture *texture, SDL_Rect texture_rect);
    void draw(SDL_Texture *texture, int x_pos, int y_pos);

    void update_screen();
    
private: 
    SDL_Renderer *renderer_;

};
