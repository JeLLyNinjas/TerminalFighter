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
        68)
    , start_(
        "Start",
        SELECTED_COLOR,
        width / 2,
        height / 2,
        width / 10,
        height / 10,
        font_path,
        68)
    , quit_(
        "Quit",
        UNSELECTED_COLOR,
        width / 2,
        3*height /4 ,
        width / 10,
        height / 10,
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
        start_.set_color(SELECTED_COLOR);
        quit_.set_color(UNSELECTED_COLOR);
    } else if (current_selection_ == QUIT){
        start_.set_color(UNSELECTED_COLOR);
        quit_.set_color(SELECTED_COLOR);
    }
}

int MainMenu::get_current_selection() {
    return current_selection_;
}
