#include "Title.h"

Title::Title(std::string t, SDL_Color c, int x, int y, int w, int h, std::string font_path, int font_size)
    : title_str(t)
    , color(c)
    , x_pos(x)
    , y_pos(y)
    , width(w)
    , height(h)
    , font(TTF_OpenFont(font_path.c_str(), font_size)) {
}

Title::~Title() {}

void Title::render(SDL_Renderer& renderer_) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, title_str.c_str(), color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(&renderer_, surface);
    SDL_Rect Message_rect;
    Message_rect.x = x_pos;
    Message_rect.y = y_pos;
    Message_rect.w = width;
    Message_rect.h = height;
    SDL_RenderCopy(&renderer_, Message, NULL, &Message_rect);
}
