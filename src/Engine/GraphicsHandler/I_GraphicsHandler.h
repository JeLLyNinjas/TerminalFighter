#pragma once

#include <string>
#include <vector>

#include "DrawRequest/DrawRequest.h"

class I_GraphicsHandler {
public:
    virtual ~I_GraphicsHandler() {}
    /**
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
    virtual void init(const std::vector<std::string>& graphic_paths) = 0;
    /**
     * Draw function
     * The draw function does not immediately draw the texture. Instead, the draw function will place
     * the <code>SDL_Texture*</code> into a queue using the <code>priority</code> parameter to determine
     * the queue order. The <code>GraphicsHandler::draw()</code> is called by the universe after the 
     * <code>universe::update_all()</code> phase.
     * @param texture will be used to SDL_RenderCopy onto the rendering target (the <code> renderer_</code>)
     * @param texture_rect is the <code>dstrect</code>, or destination rect on where the texture will
     *  be copied to. This rect defines the size, and position the texture will be rendered to
     * @param priority is used to define the order that the texture will be copied to the renderer.
     *  The GraphicPriority is an enum found in "DrawRequest/DrawRequest.h"
     * @param cleanup is used to define whether or not the draw function needs to clean up a texture.
     *   Sometimes, the texture is cached by the GraphicsHandler::game_graphics_, in which case, 
     *   you do not want to set the bool to `true`. Other times, the texture is not cached, and
     *   is passed into the function by an object, however, the object cannot delete the texture
     *   after passing it to this draw function as this function does not copy the texture onto the 
     *   renderer immediately. Refer to the main description of the draw function for explanation on 
     *   when the SDL_RenderCopy occurs.
     */
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
