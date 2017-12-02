#include <string>
#include <glog/logging.h>

#include "MainMenu.h"

// MainMenu::MainMenu(std::string font_path, int width, int height)
//     : title_(
//         "Terminal Fighter",
//         COLOR_WHITE,
//         0.25 * width, // x position relative to left side of the window
//         0.2 * height, // y position relative to the top of the window
//         0.5 * width, // width of the text area
//         0.25 * height, // height of the text area
//         font_path,
//         68)
//     , start_(
//         "Start",
//         COLOR_WHITE,
//         0.45 * width, // x position relative to left side of the window
//         0.6 * height, // y position relative to the top of the window
//         0.1 * width, // width of the text area
//         0.1 * height, // height of the text area
//         font_path,
//         68)
//     , quit_(
//         "Quit",
//         COLOR_GRAY,
//         0.45 * width, // x position relative to the left side of the window
//         0.7 * height, // y position relative to the top of the window
//         0.1 * width, // width of the text area
//         0.1 * height, // height of the text area
//         font_path,
//         68)
//     , current_selection_(START){
// }

MainMenu::MainMenu(const I_Settings& settings) : settings_(settings), title_(), current_selection_(0){
    std::string title_str;
    if (!settings.load_str(SettingsSection::MAIN_MENU, {"title", "string"}, title_str)){
        LOG(FATAL) << "Failed to load title text in MainMenu";
    }
    int color_r, color_g, color_b, window_width, window_height;
    settings.load_int(SettingsSection::MAIN_MENU, {"title", "color", "r"}, color_r);
    settings.load_int(SettingsSection::MAIN_MENU, {"title", "color", "g"}, color_g);
    settings.load_int(SettingsSection::MAIN_MENU, {"title", "color", "b"}, color_b);
    std::string default_font_path;
    if (!settings_.load_str(SettingsSection::ASSET_PATHS, {"fonts", "default"}, default_font_path)) {
        LOG(FATAL) << "Failed to load default font in MenuState";
    }
    if (!settings_.load_int(SettingsSection::VIDEO_SETTINGS, {"window", "width"}, window_width)) {
        LOG(FATAL) << "Failed to load window width in MenuState";
    }
    if (!settings_.load_int(SettingsSection::VIDEO_SETTINGS, {"window", "height"}, window_height)) {
        LOG(FATAL) << "Failed to load window height in MenuState";
    }

    double scale;
    if (!settings_.load_double(SettingsSection::MAIN_MENU, {"title", "scale"}, scale)) {
        LOG(FATAL) << "Failed to load scale in MainMenu";
    }

    int font_size;
    if (!settings_.load_int(SettingsSection::MAIN_MENU, {"title", "fontsize"}, font_size)) {
        LOG(FATAL) << "Failed to load font size in MainMenu";
    }

    int x_pos = (0.5 * double(window_width)) - (0.5 * scale * double(window_width));
    int y_pos = (0.25 * double(window_height)) - (0.5 * scale * 0.5 * double(window_height));
    int width = scale * double(window_width);
    int height = scale * (0.5 * window_height);

    title_ = TextArea(
        title_str,
        SDL_Color{
            Uint8(color_r),
            Uint8(color_g),
            Uint8(color_b)
        },
        int(x_pos),
        int(y_pos),
        int(width),
        int(height),
        default_font_path,
        font_size);
}

MainMenu::~MainMenu() {}

void MainMenu::render(SDL_Renderer& renderer) {
    title_.render(renderer);
    // start_.render(renderer);
    // quit_.render(renderer);
}
//
// void MainMenu::move_up_selection() {
//     if (current_selection_ == 0) {
//         current_selection_ = 1;
//     } else if (current_selection_ == 1){
//         current_selection_ = 0;
//     }
//     update_colors();
// }
//
// void MainMenu::move_down_selection() {
//     if (current_selection_ == 1) {
//         current_selection_ = 0;
//     } else if (current_selection_ == 0){
//         current_selection_ = 1;
//     }
//     update_colors();
// }
//
// void MainMenu::update_colors() {
//     if (current_selection_ == START) {
//         start_.set_color(COLOR_WHITE);
//         quit_.set_color(COLOR_GRAY);
//     } else if (current_selection_ == QUIT){
//         start_.set_color(COLOR_GRAY);
//         quit_.set_color(COLOR_WHITE);
//     }
// }
//
// int MainMenu::get_current_selection() {
//     return current_selection_;
// }
