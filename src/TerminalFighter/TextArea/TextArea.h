#include <string>

#include <SDL_ttf.h>

namespace{
    const SDL_Color COLOR_WHITE = {255, 255, 255};
    const SDL_Color COLOR_GRAY = {100, 100, 100};
}

class TextArea {
public:
    TextArea(std::string, SDL_Color, int, int, int, int, std::string, int);
    ~TextArea();
    void draw(SDL_Renderer& renderer);
    void set_color(SDL_Color color);
private:
    std::string text_str_;
    SDL_Color color_;
    SDL_Rect message_rect_;
    TTF_Font* font_;
};
