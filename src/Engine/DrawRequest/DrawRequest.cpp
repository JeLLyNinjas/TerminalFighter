#include "DrawRequest.h"
#include <glog/logging.h>

DrawRequest::DrawRequest(SDL_Texture* texture,
                         SDL_Rect src_rect,
                         JN_Rect dest_rect,
                         bool cleanup,
                         double angle_clockwise_from_vertical,
                         SDL_Point* rotation_point)
    : texture_(texture)
    , sdl_src_rect_(src_rect)
    , dest_rect_(dest_rect)
    , cleanup_(cleanup)
    , angle_clockwise_from_vertical_(angle_clockwise_from_vertical)
    , rotation_point_(rotation_point) {
}

SDL_Texture* DrawRequest::texture() const {
    return texture_;
}

const SDL_Rect& DrawRequest::src_rect() {
    return sdl_src_rect_;
}

const SDL_Rect& DrawRequest::dest_rect(int screen_width, int screen_height) {
    // We need to convert x and y from -1 to 1 into 0 and something like 1920
    // Some Notes. We are assuming people can run with any resolution
    // as long as it is using the 16:9 ratio.
    // 1024x576, 1152x648, 1280x720, 1366x768, 1600x900, 1920x1080, 2560x1440 3840x2160.

    // The algorithm is as follows
    // for example, say we have 1920 as our screen_width_
    // we will need a variable: half_screen_width = 960
    // we will multiply our x (which is a range of -1 to 1) with the half_screen_width.
    // so example, if we had -1, it becomes -960, and if we had 1, it would becom 960.
    // We then add them to half_screen_width (960) and we get a range of numbers between 0 and 1920.

    double half_screen_width = screen_width/2;    
    sdl_dest_rect_.x = (dest_rect_.x * half_screen_width) + half_screen_width;
    sdl_dest_rect_.w = (dest_rect_.w * half_screen_width);

    int half_screen_height = screen_height/2;    
    sdl_dest_rect_.y = (-dest_rect_.y * half_screen_height) + half_screen_height;
    sdl_dest_rect_.h = (dest_rect_.h * half_screen_height);

    //LOG(INFO) << "screen_width:" << screen_width << " screen_height:" << screen_height;
    //LOG(INFO) << "JN_Rect \tX:" << dest_rect_.x << " Y:" << dest_rect_.y << " W:" << dest_rect_.w << " H:" << dest_rect_.h;
    //LOG(INFO) << "SDL_Rect \tX:" << sdl_dest_rect_.x << " Y:" << sdl_dest_rect_.y << " W:" << sdl_dest_rect_.w << " H:" << sdl_dest_rect_.h;
    
    return sdl_dest_rect_;
}


const bool DrawRequest::cleanup() const {
    return cleanup_;
}

const double DrawRequest::angle() const {
    return angle_clockwise_from_vertical_;
}

const SDL_Point* DrawRequest::rotation_point() const {
    return rotation_point_;
}
