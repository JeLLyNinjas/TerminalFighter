#pragma once
#include <chrono>
#include <unistd.h>

#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../TextArea/TextArea.h"

namespace{
    const int START = 0;
    const int QUIT = 1;
}

class MainMenu {
public:
    MainMenu(std::string font_path, int width, int height);
    ~MainMenu();
    void render(SDL_Renderer& renderer);
    void move_up_selection();
    void move_down_selection();
    void update_colors();
    int get_current_selection();

private:
    TextArea title_;
    TextArea start_;
    TextArea quit_;
    int current_selection_;
};
