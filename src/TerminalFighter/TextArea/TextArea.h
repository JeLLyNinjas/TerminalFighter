#include <string>
#include <SDL_ttf.h>

class TextArea {
public:
    TextArea(std::string, SDL_Color, int, int, int, int, std::string, int);
    ~TextArea();
    void render(SDL_Renderer& renderer);
private:
    std::string text_str_;
    SDL_Color color_;
    int x_pos_, y_pos_, width_, height_;
    TTF_Font* font_;
};
