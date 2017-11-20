#pragma once

#include <map>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "I_GraphicsHandler.h"

class GraphicsHandler : public I_GraphicsHandler {

public:
    /*
     * Constructor for the Graphics Handler
     * Constructor that takes an SDL_Renderer and a vector of std::strings that point to graphics assets
     * @param renderer the <code>SDL_Renderer&</code> that will be used for all the graphics 
     *  manipulation and draws to the screen
     * @param graphic_paths is the path to graphics assets that you want pre-loaded upon creation
     *  of this object, rather than loading them (which you can) during the game play
     *  These assets will be loaded into <code>game_graphics_</code> 
     */
    GraphicsHandler(SDL_Renderer& renderer, std::vector<std::string> graphic_paths);
    /*
     * Used to intiate the GraphicsHandler
     * Currently just loads the entire vector of <code>graphic_paths</code> which are file paths
     * to <code>game_graphics_</code>, which is a map of std::string to SDL_Textures*
     * @param path is the relative (recommended) or absolute path to graphics assets that will 
     *  be loaded when init is called. This initial load avoids having to load assets while the
     *  level has started, and can be done when "loading" the level
     * @return has no return, but <code>internal_load_image</code> calls <code>load_image</code>
     *  which can call <code>LOG(FATAL)</code> and exit the program when an incorrect path is called
     * \note
     * having no error handling, and immediately throwing the fail is intentional. Maybe one day later
     * we should handle it more gracefully and have it load a dummy asset
     */
    void init(const std::vector<std::string>& graphic_paths);
    void draw(SDL_Texture* texture, SDL_Rect texture_rect,
              GraphicPriority priority, bool cleanup, double angle_clockwise, SDL_Point* rotation_point);

    void draw(SDL_Texture* texture, int x_pos, int y_pos,
              GraphicPriority priority, bool cleanup, double angle_clockwise, SDL_Point* rotation_point);

    void draw(SDL_Surface* surface, int x_pos, int y_pos,
              GraphicPriority priority, bool cleanup, double angle_clockwise, SDL_Point* rotation_point);

    void draw(SDL_Texture* texture, SDL_Rect texture_rect,
              GraphicPriority priority, bool cleanup);

    void draw(SDL_Texture* texture, int x_pos, int y_pos,
              GraphicPriority priority, bool cleanup);

    void draw(SDL_Surface* surface, int x_pos, int y_pos,
              GraphicPriority priority, bool cleanup);

    SDL_Texture* load_image(std::string path); /*will return textures that were loaded on init()*/
    void update_screen();

private:
    SDL_Texture* internal_load_image(std::string path);
    SDL_Renderer& renderer_;
    std::map <std::string, SDL_Texture*> game_graphics_;
    std::map <GraphicPriority, std::vector<DrawRequest>> draw_queue_;
};
