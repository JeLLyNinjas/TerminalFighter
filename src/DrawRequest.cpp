#include "DrawRequest.h"

DrawRequest::DrawRequest(SDL_Texture *texture,
                         SDL_Rect texture_rect)
    : texture_(texture)
    , texture_rect_(texture_rect)
{}

SDL_Texture* DrawRequest::texture() const {
    return texture_;
}

const SDL_Rect& DrawRequest::texture_rect() const {
    return texture_rect_;
}
