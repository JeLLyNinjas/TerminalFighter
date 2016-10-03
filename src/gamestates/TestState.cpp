#include <stdlib.h>

#include "TestState.h"

#include "GameObjectMediator.h"
#include "Universe.h"
#include "CollisionDetector.h"
#include "BasicEnemy.h"

TestState::TestState(SDL_Renderer& renderer)
    : renderer_(renderer)
    , exit_(false) {
}

gamestates::GameStateName TestState::run() {
    Keyboard keyboard = Keyboard();
    std::unique_ptr<Events> events(new Events());
    std::unique_ptr<I_CollisionDetector> collision_detector(new CollisionDetector());
    Universe universe = Universe(renderer_);
    GameObjectMediator game_object_mediator(universe, *collision_detector);
    keyboard.add_listener(this);
    events->add_listener(this);
    events->add_listener(&keyboard);
    universe.add_game_service(std::move(events));
    universe.add_game_service(std::move(collision_detector));
    MissileLauncher test_launcher = MissileLauncher(Team::FRIENDLY, game_object_mediator);
    //Render red filled quad
    Delay delayer(false);

    // for (int i = 0; i < SCREEN_WIDTH - 100; i += 100) {
    //     std::unique_ptr<BasicEnemy> enemy(new BasicEnemy(i, 100, 0, 0));
    //     game_object_mediator.add_game_object(Team::ENEMY, std::move(enemy));
    // }

    for (;;) {
        test_launcher.create_missile(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, rand() % 4, rand() % 4);
        std::unique_ptr<BasicEnemy> enemy(new BasicEnemy(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 0, 0));
        game_object_mediator.add_game_object(Team::ENEMY, std::move(enemy));

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
    SDL_FreeSurface(frame_rate_surface);
}

/* listeners */

void TestState::handle_key_press(const std::string& keypress) {
    if (keypress == "ESC") {
        exit_ = true;
    }

    printf("Key returned was: %s\n", keypress.c_str());
}

void TestState::notify_events(const SDL_Event& e) {
    switch (e.type) {
        case SDL_QUIT:
            printf("SDL_QUIT was called!\n");
            exit_ = true;
            break;
    }
}

