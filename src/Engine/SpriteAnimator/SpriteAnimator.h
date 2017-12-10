#pragma once

#include "GraphicsHandler/I_GraphicsHandler"

class SpriteAnimator {
    public:
    /**
     * Creates a Sprite Animator object
     * Uses the <code>SDL_Texture*</code> to create a <code>SDL_Rect</code> that represents the
     * spritesheet.
     */
    SpriteAnimator(SDL_Texture* texture);
    /**
     * Get's the next <code>SDL_Rect</code>
     * @return <code>SDL_Rect</code> for the next frame in the spritesheet. This 
     *   <code>SDL_Rect</code> is to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect
     */
    SDL_Rect get_next_frame();
    /**
     * Get's the next <code>SDL_Rect</code>
     * @param returned_frame is just a way for the user to check what frame 
     *   was returned when <code>SpriteAnimator::get_next_frame()</code> was called
     * @return <code>SDL_Rect</code> for the next frame in the spritesheet. This 
     *   <code>SDL_Rect</code> is to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect
     */
    SDL_Rect get_next_frame(int &returned_frame);
    /**
     * Get's a specific <code>SDL_Rect</code>
     * @param frame is <code>int</code> specifying which frame (SDL_Rect) of the 
     *   sprite sheet the function should return
     * @return <code>SDL_Rect</code> for the specified frame in the spritesheet. This 
     *   <code>SDL_Rect</code> is to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect
     */
    SDL_Rect get_frame(int frame);

    /**
     * @return total number of frames
     */
    int get_total_frames();

    private:

    bool using_grid_;
    int total_frames_;
    SDL_Rect total_sprite_sheet_size_;


};
