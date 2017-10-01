#pragma once

#include <string>
#include <vector>

#include "DrawRequest/DrawRequest.h"

class I_GraphicsHandler {
public:
    virtual ~I_GraphicsHandler() {}
    virtual void init(std::vector<std::string> graphic_paths) = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect texture_rect, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Texture* texture, int x_pos, int y_pos, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Surface* surface, int x_pos, int y_pos, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect texture_rect,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual void draw(SDL_Texture* texture, int x_pos, int y_pos,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual void draw(SDL_Surface* surface, int x_pos, int y_pos,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual SDL_Texture* load_image(std::string path) = 0;
    virtual void update_screen() = 0;
};
