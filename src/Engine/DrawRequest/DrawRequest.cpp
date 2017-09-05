#include "DrawRequest.h"

DrawRequest::DrawRequest(SDL_Texture* texture,
                         SDL_Rect texture_rect,
                         bool is_flyweight,
                         double angle_clockwise_from_vertical,
                         SDL_Point* rotation_point)
    : texture_(texture)
    , texture_rect_(texture_rect)
    , is_flyweight_(is_flyweight)
    , angle_clockwise_from_vertical_(angle_clockwise_from_vertical)
    , rotation_point_(rotation_point) {
}

SDL_Texture* DrawRequest::texture() const {
    return texture_;
}

const SDL_Rect& DrawRequest::texture_rect() const {
    return texture_rect_;
}

const bool DrawRequest::is_flyweight() const {
    return is_flyweight_;
}

const double DrawRequest::angle() const {
    return angle_clockwise_from_vertical_;
}

const SDL_Point* DrawRequest::rotation_point() const {
    return rotation_point_;
}
