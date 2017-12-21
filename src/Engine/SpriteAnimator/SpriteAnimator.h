#pragma once

#include "../Engine/GraphicsHandler/I_GraphicsHandler.h"
#include <vector>

class SpriteAnimator {
public:
    /**
     * Creates a Sprite Animator object
     */
    SpriteAnimator();
    /**
     * Uses the <code>SDL_Texture*</code> to create a <code>SDL_Rect</code> that represents the
     * spritesheet.
     */
    int init(SDL_Texture* texture, int rows, int cols, int on_every);
    /**
     * Uses the <code>SDL_Texture*</code> to create a <code>SDL_Rect</code> that represents the
     * spritesheet.
     */
    int init(SDL_Texture* texture, int rows, int cols, int on_every, std::vector<int> draw_order);
    /**
     * Get's the next <code>SDL_Rect</code>
     * @return <code>SDL_Rect</code> for the next frame in the spritesheet. This
     *   <code>SDL_Rect</code> is meant to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect
     */
    SDL_Rect get_next_frame();
    /**
     * Get's the <code>SDL_Rect</code>
     * @param returned_frame is just a way for the user to check what frame
     *   was returned when <code>SpriteAnimator::get_next_frame()</code> was called
     * @return <code>SDL_Rect</code> for the <code>current_frame_</code> in the spritesheet. This
     *   <code>SDL_Rect</code> is to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect. The <code>current_frame_</code> will be advanced at the end of the function
     */
    SDL_Rect get_next_frame(int& returned_frame);
    /**
     * Get's a specific <code>SDL_Rect</code>
     * @param frame is <code>int</code> specifying which frame (SDL_Rect) of the
     *   sprite sheet the function should return
     * @return <code>SDL_Rect</code> for the <code>current_frame_</code> in the spritesheet. This
     *   <code>SDL_Rect</code> is to be used in <code>GraphicsHandler::draw()</code> function
     *   as the src_rect. The <code>current_frame_</code> will be advanced at the end of the function
     */
    SDL_Rect get_frame(int frame);

    /**
     * @return total number of frames
     */
    int get_total_frames();

    bool is_initialized();

private:

    int rows_;
    int cols_;
    int incrementor_;
    int current_index_;
    int on_every_;
    std::vector<int> draw_order_;
    SDL_Rect total_sprite_sheet_size_;
    bool initialized_;

};
