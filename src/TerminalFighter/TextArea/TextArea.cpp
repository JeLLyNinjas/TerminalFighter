#include "TextArea.h"

TextArea::TextArea(std::string t, SDL_Color c, int x, int y, int w, int h, std::string font_path, int font_size)
    : text_str_(t)
    , color_(c)
    , font_(TTF_OpenFont(font_path.c_str(), font_size)) {
    message_rect_.x = x;
    message_rect_.y = y;
    message_rect_.w = w;
    message_rect_.h = h;
}

TextArea::~TextArea() {}

void TextArea::draw(SDL_Renderer& renderer_) {
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text_str_.c_str(), color_);
    SDL_Texture* message = SDL_CreateTextureFromSurface(&renderer_, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(&renderer_, message, NULL, &message_rect_);
    SDL_DestroyTexture(message);
}

void TextArea::set_color(SDL_Color color) {
    this->color_ = color;
}
