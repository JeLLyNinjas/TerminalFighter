#pragma once
#include <chrono>
#include <unistd.h>

#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../TextArea/TextArea.h"


class MainMenu {
public:
    enum Options { START, QUIT };

    MainMenu(std::string font_path, int width, int height);
    ~MainMenu();
    void draw(SDL_Renderer& renderer);
    void move_up_selection();
    void move_down_selection();
    void update();
    MainMenu::Options get_current_selection();

private:
    std::unique_ptr<I_TextArea> title_;
    std::vector<std::unique_ptr<I_TextArea>> options_;
    Options current_selection_;
};
