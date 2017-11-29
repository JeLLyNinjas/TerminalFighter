#include <string>
#include <glog/logging.h>

#include "MainMenu.h"

MainMenu::MainMenu(std::string font_path, int width, int height)
    : title_(
        "Terminal Fighter",
        WHITE,
        0.25 * width,
        0.2 * height,
        0.5 * width,
        0.25 * height,
        font_path,
        68)
    , start_(
        "Start",
        WHITE,
        0.45 * width,
        0.6 * height,
        0.1 * width,
        0.1 * height,
        font_path,
        68)
    , quit_(
        "Quit",
        GRAY,
        0.45 * width,
        0.7 * height ,
        0.1 * width,
        0.1 * height,
        font_path,
        68)
    , current_selection_(START){
}

MainMenu::~MainMenu() {}

void MainMenu::render(SDL_Renderer& renderer) {
    title_.render(renderer);
    start_.render(renderer);
    quit_.render(renderer);
}

void MainMenu::move_up_selection() {
    current_selection_ = (2 + (current_selection_ + 1) % 2) % 2;
    update_colors();
}

void MainMenu::move_down_selection() {
    current_selection_ = (2 + (current_selection_ - 1) % 2) % 2;
    update_colors();
}

void MainMenu::update_colors() {
    if (current_selection_ == START) {
        start_.set_color(WHITE);
        quit_.set_color(GRAY);
    } else if (current_selection_ == QUIT){
        start_.set_color(GRAY);
        quit_.set_color(WHITE);
    }
}

int MainMenu::get_current_selection() {
    return current_selection_;
}
