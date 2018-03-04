#include "Animator.h"

Animator::Animator()
    : initialized_(false)
{}

// Keeping this as an init right now because the objects may not
int Animator::init(SDL_Texture* texture, int rows, int cols, int period) {
    period_ = period;
    rows_ = rows;
    cols_ = cols;
    current_index_ = 0;

    //If there was no draw_order given as an argument, we will create a default
    if (draw_order_.size() == 0) {
        for (int i = 0; i < rows * cols; i++) {
            draw_order_.push_back(i);
        }
    }

    // We will run off the assumption that the given
    // spritesheet has it's starting sprites on 0,0.
    // If there is padding... manually get rid of it
    // using something like gimp 2.0 for now.
    total_sprite_sheet_size_.x = 0;
    total_sprite_sheet_size_.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &total_sprite_sheet_size_.w, &total_sprite_sheet_size_.h);
    initialized_ = true;
    return 0;
}

int Animator::init(SDL_Texture* texture, int rows, int cols, int period, std::vector<int> draw_order) {
    draw_order_ = draw_order;
    return init(texture, rows, cols, period);
}


SDL_Rect Animator::get_next_frame(int& returned_frame) {
    // We want to be able to call this function, and start with frame 0
    // So we advance the frame at the end of this function
    returned_frame = draw_order_.at(current_index_);
    SDL_Rect return_rect;

    int on_row = draw_order_.at(current_index_) / cols_; //integer division for the floor
    int on_col = draw_order_.at(current_index_) % (rows_ - 1);

    return_rect.w = total_sprite_sheet_size_.w / cols_;
    return_rect.h = total_sprite_sheet_size_.h / rows_;
    return_rect.x = on_col * (total_sprite_sheet_size_.w / cols_);
    return_rect.y = on_row * (total_sprite_sheet_size_.h / rows_);

    incrementor_++;
    incrementor_ = incrementor_ % period_;

    if (incrementor_ == 0) {
        current_index_++;
    }

    current_index_ = current_index_ % draw_order_.size();

    return return_rect;
}

SDL_Rect Animator::get_next_frame() {
    int throw_away;
    return get_next_frame(throw_away);
}

bool Animator::is_initialized() {
    return initialized_;
}
