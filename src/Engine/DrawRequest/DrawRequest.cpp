#include "DrawRequest.h"

DrawRequest::DrawRequest(SDL_Texture* texture,
                         SDL_Rect src_rect,
                         SDL_Rect dest_rect,
                         bool cleanup,
                         double angle_clockwise_from_vertical,
                         SDL_Point* rotation_point)
    : texture_(texture)
    , src_rect_(src_rect)
    , dest_rect_(dest_rect)
    , cleanup_(cleanup)
    , angle_clockwise_from_vertical_(angle_clockwise_from_vertical)
    , rotation_point_(rotation_point) {
}

SDL_Texture* DrawRequest::texture() const {
    return texture_;
}

const SDL_Rect& DrawRequest::dest_rect() const {
    return dest_rect_;
}

const SDL_Rect& DrawRequest::src_rect() const {
    return src_rect_;
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
