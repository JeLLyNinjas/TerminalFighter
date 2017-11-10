#include <string>
#include <SDL_ttf.h>

class Title {
    std::string title_str;
    SDL_Color color;
    int x_pos;
    int y_pos;
    int width;
    int height;
    TTF_Font* font;
public:
    Title() : title_str(), color(), x_pos(0), y_pos(0), width(0), height(0), font() {};
    Title(std::string, SDL_Color, int, int, int, int, std::string, int);
    ~Title();
    void render(SDL_Renderer& renderer);
};
