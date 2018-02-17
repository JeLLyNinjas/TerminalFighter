#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "JN_Rect/JN_Rect.h"
#include "Jn_Ttf/Jn_Ttf.h"
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
     * and exit the program when an invalid path is called.
     * \note
     * There is no real error handling here. If an invalid path is given, the function will throw a fatal
     * error and then the program will exit.
     */
    virtual void init(const std::vector<std::string>& graphic_paths) = 0;
    /**
     * Used as a helper function to create a JN_Rect
     * //TODO comment on how this uses the 1-1 gamespace and how it works
     * \note
     * 'JN' stands for JellyNinjas
     */
    virtual JN_Rect create_jn_rect(double x,
            double y,
            double w,
            double h) = 0;

    virtual SDL_Rect create_sdl_rect(int x,
            int y,
            int w,
            int h) = 0;
    /**
     * Draw function
     * This draw function does not immediately draw the texture onto the screen. Instead, the draw function
     * will place the <code>SDL_Texture*</code> into a queue using the <code>priority</code> parameter to determine
     * the queue order. The queue is then drawn by <code>Universe::draw_to_screen()</code>.
     * @param texture will be used to SDL_RenderCopy onto the rendering target (the <code> renderer_</code>)
     * @param dest_rect is the <code>dstrect</code>, or destination rect on where the texture will
     *  be copied to. This rect defines the size, and position the texture will be rendered to
     * @param priority is used to define the order that the texture will be copied to the renderer.
     *  The GraphicPriority is an enum found in "DrawRequest/DrawRequest.h"
     * @param cleanup is used to define whether or not the draw function needs to clean up a texture.
     *   Set this to false when the texture passed to this function is cached. For example,
     *   <code>GraphicsHandler::load_image()</code> caches the image. So if the calling object uses that
     *   function to load the image, set cleanup to false.
     *   Set this value to true when you need the function to cleanup the texture for you.
     *   For example, when an object creates a texture, and will not hold onto the texture (no cache). You will need
     *   to set the cleanup value to true. This is because the object that passes this texture onto the
     *   draw function is not allowed to call <code>SDL_DestroyTexture</code> to free the texture.
     *   The object is not allowed to free the texture because this function does not copy the texture
     *   onto the renderer immediately.
     *   Refer to the main description of the draw function for explanation on when the SDL_RenderCopy occurs.
     * @param angle_clockwise is a variable defined in degrees that indicates the rotation that will be applied to
     *   dest_rect, rotating in a clockwise direction.
     * @param rotation_point is a point that defines where the rotation of angle_clockwise will rotate around.
     *   set to NULL for rotation to be done around the center (dest_rect.w/2, dest_rect.h/2).
     */
    virtual void draw(SDL_Texture* texture,
                      SDL_Rect src_rect,
                      JN_Rect dest_rect,
                      GraphicPriority priority,
                      bool cleanup,
                      double angle_clockwise,
                      SDL_Point* rotation_point) = 0;

    virtual void draw(SDL_Surface* surface,
                      SDL_Rect src_rect,
                      JN_Rect dest_rect,
                      GraphicPriority priority,
                      bool cleanup,
                      double angle_clockwise,
                      SDL_Point* rotation_point) = 0;
    virtual void draw_text(std::string text, 
            RenderType type,
            std::string font_path,
            SDL_Color color,
            int font_render_size,
            double font_output_size) = 0;

    virtual SDL_Texture* load_image(std::string path) = 0;
    /**
     * Update the screen
     * Will call a <code>SDL_RenderCopyEx()</code> to copy the textures onto the renderer.
     * This function takes the queue the <code>draw</code> function has created, and copies all
     * of the textures onto the renderer depending on their priority. While the function is copying
     * the <code>SDL_Texture*</code> onto the screen, it may delete the pointer depending on the
     * <code>cleanup</code> boolean flag.
     */
    virtual void update_screen() = 0;
};
