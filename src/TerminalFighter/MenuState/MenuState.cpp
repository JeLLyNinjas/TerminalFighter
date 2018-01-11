#include <glog/logging.h>

#include "MenuState.h"

MenuState::MenuState(SDL_Renderer& renderer, const I_Settings& settings)
    : renderer_(renderer)
    , settings_(settings) {
}

MenuState::~MenuState() {}

gamestates::GameStateName MenuState::run() {
    std::string default_font_path;

    if (!settings_.load_str(SettingsSection::ASSET_PATHS, {"fonts", "default"}, default_font_path)) {
        LOG(FATAL) << "Failed to load default font in MenuState";
    }
    int window_width, window_height;

    if (!settings_.load_int(SettingsSection::VIDEO_SETTINGS, {"window", "width"}, window_width)) {
        LOG(FATAL) << "Failed to load window width in MenuState";
    }

    if (!settings_.load_int(SettingsSection::VIDEO_SETTINGS, {"window", "height"}, window_height)) {
        LOG(FATAL) << "Failed to load window height in MenuState";
    }

    Delay delayer(false, default_font_path);

    MainMenu main_menu(default_font_path, window_width, window_height);
    std::vector<std::string> graphic_paths;
    GraphicsHandler graphics_handler(renderer_, graphic_paths, window_width, window_height);

    for (;;) {
        main_menu.draw(renderer_);
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    LOG(INFO) << "SDL_QUIT was called";
                    return gamestates::EXIT;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                            LOG(INFO) << "Enter was pressed!";

                            if (main_menu.get_current_selection() == MainMenu::Options::START) {
                                LOG(INFO) << "Start selected";
                                return gamestates::TEST;
                            } else if (main_menu.get_current_selection() == MainMenu::Options::QUIT) {
                                LOG(INFO) << "Quit selected";
                                return gamestates::EXIT;
                            }

                            break;

                        case SDLK_UP:
                            main_menu.move_up_selection();
                            break;

                        case SDLK_DOWN:
                            main_menu.move_down_selection();
                            break;

                    }
            }
        }

        main_menu.update();

        display_debug_frames(&delayer);
        //delay and draw to screen should stick together in the order: delay -> draw
        delayer.delay_with_fps(60);
        graphics_handler.update_screen();
    }

    return gamestates::EXIT;
}

gamestates::GameStateName MenuState::name() const {
    return gamestates::MAIN_MENU;
}

void MenuState::display_debug_frames(Delay* delayer) {
    SDL_Surface* frame_rate_surface = delayer->grab_frame_rate();
    SDL_Texture* frame_rate_texture = SDL_CreateTextureFromSurface(&renderer_, frame_rate_surface);
    SDL_FreeSurface(frame_rate_surface);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 70; // controls the height of the rect
    SDL_RenderCopy(&renderer_, frame_rate_texture, NULL, &Message_rect);
    SDL_DestroyTexture(frame_rate_texture);
}
