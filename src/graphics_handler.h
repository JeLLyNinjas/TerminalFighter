#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <SDL_image.h>

class GraphicsHandler {

public:
    GraphicsHandler(SDL_Renderer *renderer);
    void init();
    void draw(SDL_Texture *texture, SDL_Rect texture_rect);
    void draw(SDL_Texture *texture, int x_pos, int y_pos);
    SDL_Texture *load_image(std::string path); /*will return textures that were loaded on init()*/

    void update_screen();

private:
    SDL_Texture *internal_load_image(std::string path);
    SDL_Renderer *renderer_;
    std::map <std::string, SDL_Texture *> game_graphics_;
};
