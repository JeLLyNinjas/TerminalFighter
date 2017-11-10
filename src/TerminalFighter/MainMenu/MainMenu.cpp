#include <glog/logging.h>

#include <fstream>
#include <string>
#include <iostream>
#include "MainMenu.h"

MainMenu::MainMenu(std::string font_path) {
    title = Title("Terminal Fighter", {255, 255, 255},
                  400, 200, 900, 250, font_path, 68);
}

MainMenu::~MainMenu() {}

void MainMenu::render(SDL_Renderer& renderer) {
    title.render(renderer);
}
