#include "TextArea.h"

TextArea::TextArea(std::string t, SDL_Color c, int x, int y, int w, int h, std::string font_path, int font_size)
    : text_str_(t)
    , color_(c)
    , x_pos_(x)
    , y_pos_(y)
    , width_(w)
    , height_(h)
    , font_(TTF_OpenFont(font_path.c_str(), font_size)) {
}

TextArea::~TextArea() {}

void TextArea::render(SDL_Renderer& renderer_) {
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text_str_.c_str(), color_);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(&renderer_, surface);
    SDL_FreeSurface(surface);
    SDL_Rect Message_rect;
    Message_rect.x = x_pos_;
    Message_rect.y = y_pos_;
    Message_rect.w = width_;
    Message_rect.h = height_;
    SDL_RenderCopy(&renderer_, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
}

void TextArea::set_color(SDL_Color color) {
    this->color_ = color;
}
