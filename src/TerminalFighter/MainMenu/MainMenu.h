#pragma once
#include <chrono>
#include <unistd.h>

#include <SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../TextArea/TextArea.h"

class MainMenu {
public:
    MainMenu(std::string font_path);
    ~MainMenu();
    void render(SDL_Renderer& renderer);

private:
    TextArea title_;
};
