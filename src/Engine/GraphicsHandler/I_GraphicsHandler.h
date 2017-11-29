#pragma once

#include <string>
#include <vector>

#include "DrawRequest/DrawRequest.h"

class I_GraphicsHandler {
public:
    virtual ~I_GraphicsHandler() {}
    /**
     * Used to intiate the GraphicsHandler
     * Loads the vector of <code>graphic_paths</code> which are file paths
     * to <code>GraphicsHandler::game_graphics_</code>, which is a map of std::string to SDL_Textures*
     * @param path is the relative (recommended) or absolute path to graphics assets that will 
     *  be loaded when init is called. This initial load avoids having to load assets while the
     *  level has started, and can be done when "loading" the level
     * @return returns <code>void</code>. However, <code>GraphicsHandler::internal_load_image()</code> calls 
     * <code>load_image</code> which _can_ potentially call <code>LOG(FATAL)</code>
     * and exit the program when an incorrect path is called.
     * \note
     * We have no real error handling here. If an invalid path is given, it means an object may not have
     * an asset, so calling exiting the program is kind of appropriate. However, maybe one day, we should
     * handle it gracefully and have it load a dummy asset.
     */
    virtual void init(const std::vector<std::string>& graphic_paths) = 0;
    /**
     * Draw function
     * The draw function does not immediately draw the texture. Instead, the draw function will place
     * the <code>SDL_Texture*</code> into a queue using the <code>priority</code> parameter to determine
     * the queue order. The queue is then drawn by <code>Universe::draw_to_screen()</code>, which is called
     * after what should currently be the <code>Universe::draw_all()</code>. 
     * <code>GraphicsHandler::draw()</code> is called by the universe after the 
     * @param texture will be used to SDL_RenderCopy onto the rendering target (the <code> renderer_</code>)
     * @param dest_rect is the <code>dstrect</code>, or destination rect on where the texture will
     *  be copied to. This rect defines the size, and position the texture will be rendered to
     * @param priority is used to define the order that the texture will be copied to the renderer.
     *  The GraphicPriority is an enum found in "DrawRequest/DrawRequest.h"
     * @param cleanup is used to define whether or not the draw function needs to clean up a texture.
     *   Set this to false when the texture passed to this function is cached. 
     *   Sometimes, the texture is cached by the GraphicsHandler::game_graphics_, in which case, 
     *   you do not want to set the bool to `true` or else this function will delete the cached pointer.
     *   Set this value to true when you need the function to cleanup the texture for you.
     *   When an object creates a texture, and will not hold onto the texture (no cache). You will need
     *   to set the cleanup value to true. This is because the object that passes this texture onto the 
     *   draw function is not allowed to call <code>SDL_DestroyTexture</code> to free the texture.
     *   This function does not copy the texture onto the renderer immediately. 
     *   Refer to the main description of the draw function for explanation on when the SDL_RenderCopy occurs.
     * @param angle_clockwise is a variable defined in degrees that indicates the rotation that will be applied to
     *   dest_rect 
     */
    virtual void draw(SDL_Texture* texture, SDL_Rect dest_rect, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Texture* texture, int x_pos, int y_pos, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Surface* surface, int x_pos, int y_pos, GraphicPriority priority,
                      bool cleanup, double angle_clockwise, SDL_Point* rotation_point) = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect dest_rect,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual void draw(SDL_Texture* texture, int x_pos, int y_pos,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual void draw(SDL_Surface* surface, int x_pos, int y_pos,
                      GraphicPriority priority, bool cleanup) = 0;
    virtual SDL_Texture* load_image(std::string path) = 0;
    virtual void update_screen() = 0;
};
