#include <string>
#include <glog/logging.h>

#include "TF_Colors/TF_Colors.h"

#include "MainMenu.h"

MainMenu::MainMenu(std::string font_path, int width, int height)
    : title_(std::make_unique<TextArea>(
        "Terminal Fighter",
        TF_Colors::WHITE,
        0.25 * width, // x position relative to left side of the window
        0.2 * height, // y position relative to the top of the window
        0.5 * width, // width of the text area
        0.25 * height, // height of the text area
        font_path,
        68))
    , current_selection_(Options::START)
{
        options_.push_back(std::make_unique<TextArea>(
            "Start",
            TF_Colors::WHITE,
            0.45 * width,
            0.6 * height,
            0.1 * width,
            0.1 * height,
            font_path,
            68
        ));
        options_.push_back(std::make_unique<TextArea>(
            "Quit",
            TF_Colors::GRAY,
            0.45 * width,
            0.7 * height,
            0.1 * width,
            0.1 * height,
            font_path,
            68
        ));
}

MainMenu::~MainMenu() {}

void MainMenu::draw(SDL_Renderer& renderer) {
    title_->draw(renderer);
    options_[Options::START]->draw(renderer);
    options_[Options::QUIT]->draw(renderer);
}

void MainMenu::move_up_selection() {
    if (current_selection_ == Options::START) {
        current_selection_ = Options::QUIT;
    } else if (current_selection_ == Options::QUIT){
        current_selection_ = Options::START;
    }
}

void MainMenu::move_down_selection() {
    if (current_selection_ == Options::QUIT) {
        current_selection_ = Options::START;
    } else if (current_selection_ == Options::START){
        current_selection_ = Options::QUIT;
    }
}

void MainMenu::update() {
    if (current_selection_ == Options::START) {
        options_[Options::START]->set_color(TF_Colors::WHITE);
        options_[Options::QUIT]->set_color(TF_Colors::GRAY);
    } else if (current_selection_ == Options::QUIT){
        options_[Options::START]->set_color(TF_Colors::GRAY);
        options_[Options::QUIT]->set_color(TF_Colors::WHITE);
    }
}

MainMenu::Options MainMenu::get_current_selection() {
    return current_selection_;
}
