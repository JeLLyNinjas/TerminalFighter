#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "I_GraphicsHandler.h"

class GraphicsHandler : public I_GraphicsHandler {

public:
    GraphicsHandler(SDL_Renderer& renderer);
    void init();
    void draw(SDL_Texture* texture, SDL_Rect texture_rect, GraphicPriority priority, bool is_flyweight);
    void draw(SDL_Texture* texture, int x_pos, int y_pos, GraphicPriority priority, bool is_flyweight);
    void draw(SDL_Surface* surface, int x_pos, int y_pos, GraphicPriority priority, bool is_flyweight);
    SDL_Texture* load_image(std::string path); /*will return textures that were loaded on init()*/
    void update_screen();

private:
    SDL_Texture* internal_load_image(std::string path);
    SDL_Renderer& renderer_;
    std::map <std::string, SDL_Texture*> game_graphics_;
    std::map <GraphicPriority, std::vector<DrawRequest>> draw_queue_;
};
