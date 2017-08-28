#include "DrawRequest.h"

DrawRequest::DrawRequest(SDL_Texture* texture,
                         SDL_Rect texture_rect,
                         bool is_flyweight)
    : texture_(texture)
    , texture_rect_(texture_rect)
    , is_flyweight_(is_flyweight) {
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
