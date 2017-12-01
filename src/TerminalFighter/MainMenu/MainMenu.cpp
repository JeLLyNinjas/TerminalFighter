#include <string>
#include <glog/logging.h>

#include "MainMenu.h"

MainMenu::MainMenu(std::string font_path, int width, int height)
    : title_(
        "Terminal Fighter",
        COLOR_WHITE,
        0.25 * width, // x position relative to left side of the window
        0.2 * height, // y position relative to the top of the window
        0.5 * width, // width of the text area
        0.25 * height, // height of the text area
        font_path,
        68)
    , start_(
        "Start",
        COLOR_WHITE,
        0.45 * width, // x position relative to left side of the window
        0.6 * height, // y position relative to the top of the window
        0.1 * width, // width of the text area
        0.1 * height, // height of the text area
        font_path,
        68)
    , quit_(
        "Quit",
        COLOR_GRAY,
        0.45 * width, // x position relative to the left side of the window
        0.7 * height, // y position relative to the top of the window
        0.1 * width, // width of the text area
        0.1 * height, // height of the text area
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
    if (current_selection_ == 0) {
        current_selection_ = 1;
    } else if (current_selection_ == 1){
        current_selection_ = 0;
    }
    update_colors();
}

void MainMenu::move_down_selection() {
    if (current_selection_ == 1) {
        current_selection_ = 0;
    } else if (current_selection_ == 0){
        current_selection_ = 1;
    }
    update_colors();
}

void MainMenu::update_colors() {
    if (current_selection_ == START) {
        start_.set_color(COLOR_WHITE);
        quit_.set_color(COLOR_GRAY);
    } else if (current_selection_ == QUIT){
        start_.set_color(COLOR_GRAY);
        quit_.set_color(COLOR_WHITE);
    }
}

int MainMenu::get_current_selection() {
    return current_selection_;
}
