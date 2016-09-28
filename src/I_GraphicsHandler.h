#pragma once

#include "DrawRequest.h"

class I_GraphicsHandler {
public:
    virtual ~I_GraphicsHandler() {}
    virtual void init() = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect texture_rect, GraphicPriority priority) = 0;
    virtual void draw(SDL_Texture* texture, int x_pos, int y_pos, GraphicPriority priority) = 0;
    virtual SDL_Texture* load_image(std::string path) = 0;
    virtual void update_screen() = 0;
};
