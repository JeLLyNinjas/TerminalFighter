#pragma once
#include <chrono>
#include <unistd.h>

#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../TextArea/TextArea.h"


class MainMenu {
public:
    MainMenu(std::string font_path, int width, int height);
    ~MainMenu();
    enum Options { START, QUIT };
    void draw(SDL_Renderer& renderer);
    void move_up_selection();
    void move_down_selection();
    void update();
    MainMenu::Options get_current_selection();

private:
    TextArea title_;
    std::vector<TextArea> options_;
    Options current_selection_;
};
