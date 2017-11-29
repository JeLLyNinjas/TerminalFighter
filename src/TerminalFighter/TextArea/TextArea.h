#include <string>
#include <SDL_ttf.h>

#define WHITE {255, 255, 255}
#define GRAY {100, 100, 100}

class TextArea {
public:
    TextArea(std::string, SDL_Color, int, int, int, int, std::string, int);
    ~TextArea();
    void render(SDL_Renderer& renderer);
    void set_color(SDL_Color color);
private:
    std::string text_str_;
    SDL_Color color_;
    int x_pos_, y_pos_, width_, height_;
    TTF_Font* font_;
};
