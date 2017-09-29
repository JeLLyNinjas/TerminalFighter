#include <stdlib.h>

#include <glog/logging.h>

#include "TestState.h"

#include "Team/Team.h"
#include "GameObjectMediator/GameObjectMediator.h"
#include "Universe/Universe.h"
#include "CollisionDetector/CollisionDetector.h"
#include "GraphicsHandler/GraphicsHandler.h"
#include "Settings/Settings.h"

#include "MainCharacter/MainCharacter.h"
#include "BasicEnemy/BasicEnemy.h"
#include "Terminal/Terminal.h"
#include "TargetingSystem/TargetingSystem.h"

TestState::TestState(SDL_Renderer& renderer, const I_Settings& settings)
    : exit_(false)
    , renderer_(renderer)
    , settings_(settings) {
}

gamestates::GameStateName TestState::run() {
    int screen_width = settings_.video_settings()["window"]["width"].as<int>();
    int screen_height = settings_.video_settings()["window"]["height"].as<int>();

    // Initialize engine critical components
    GraphicsHandler graphics_handler(renderer_);
    Universe universe(graphics_handler);
    std::unique_ptr<Events> events(new Events());
    std::unique_ptr<I_CollisionDetector> collision_detector(new CollisionDetector());
    GameObjectMediator game_object_mediator(universe, *collision_detector);
    Keyboard keyboard;

    // Setup engine critical components
    graphics_handler.init();
    keyboard.add_listener(this);
    events->add_listener(this);
    events->add_listener(&keyboard);
    universe.add_game_service(std::move(events));
    universe.add_game_service(std::move(collision_detector));

    // Create game pieces

    // Setup MainCharacter
    double main_character_x = screen_width / 2;
    double main_character_y = screen_height - 100;

    // Font paths
    std::string default_font_path =
        settings_.asset_paths()["fonts"]["default"].as<std::string>();

    // Graphic paths
    std::string main_character_graphic =
        settings_.asset_paths()["graphics"]["main_character"].as<std::string>();
    std::string missile_graphic =
        settings_.asset_paths()["graphics"]["missile"].as<std::string>();
    std::string terminal_graphic =
        settings_.asset_paths()["graphics"]["terminal"].as<std::string>();
    std::string basic_enemy_graphic =
        settings_.asset_paths()["graphics"]["basic_enemy"].as<std::string>();

    // Construction
    std::unique_ptr<MainCharacter> main_character(
        new MainCharacter(main_character_x,
                          main_character_y,
                          100, main_character_graphic));
    std::unique_ptr<MissileLauncher> launcher(
        new MissileLauncher(
            Team::FRIENDLY,
            game_object_mediator,
            missile_graphic,
            terminal_graphic,
            default_font_path,
            main_character_x,
            main_character_y));
    keyboard.add_listener(&(*launcher));
    main_character->add_weapon(std::move(launcher));

    // Add game pieces to game
    game_object_mediator.add_game_object(Team::FRIENDLY, std::move(main_character));

    Delay delayer(false, default_font_path);

    for (;;) {
        if (rand() % 45 == 0) {
            std::unique_ptr<BasicEnemy> enemy(
                new BasicEnemy(rand() % screen_width, rand() % screen_height, 0, 0, 5));
            game_object_mediator.add_game_object(Team::ENEMY, std::move(enemy));
        }

        if (exit_) {
            return gamestates::EXIT;
        }

        universe.update_all();
        universe.draw_all();
        display_debug_frames_(&delayer);
        //delay and draw to screen should stick together in the order: delay -> draw
        delayer.delay_with_fps(60);
        universe.draw_to_screen();
    }

    return gamestates::EXIT;
}

gamestates::GameStateName TestState::name() const {
    return gamestates::TEST;
}

void TestState::display_debug_frames_(Delay* delayer) {
    SDL_Surface* frame_rate_surface = delayer->grab_frame_rate();
    SDL_Texture* frame_rate_texture = SDL_CreateTextureFromSurface(&renderer_, frame_rate_surface);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 70; // controls the height of the rect
    SDL_RenderCopy(&renderer_, frame_rate_texture, NULL, &Message_rect);
    SDL_DestroyTexture(frame_rate_texture);
    SDL_FreeSurface(frame_rate_surface);
}

/* listeners */

void TestState::handle_key_press(const std::string& keypress) {
    if (keypress == "ESC") {
        exit_ = true;
    }

    LOG(INFO) << "Key returned was: " << keypress.c_str();
}

void TestState::notify_events(const SDL_Event& e) {
    switch (e.type) {
        case SDL_QUIT:
            LOG(INFO) << "SDL_QUIT was called!";
            exit_ = true;
            break;
    }
}

