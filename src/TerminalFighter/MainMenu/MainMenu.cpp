#include <string>
#include <glog/logging.h>

#include "MainMenu.h"

MainMenu::MainMenu(std::string font_path, int width, int height)
    : title_(
        "Terminal Fighter",
        {255, 255, 255},
        width / 4,
        height / 5,
        width / 2,
        height / 4,
        font_path,
        68) {
}

MainMenu::~MainMenu() {}

void MainMenu::render(SDL_Renderer& renderer) {
    title_.render(renderer);
}
