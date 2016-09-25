#include "TestState.h"

#include "GameObjectMediator.h"
#include "Universe.h"
#include "CollisionDetector.h"

TestState::TestState(SDL_Renderer* renderer)
: renderer_(renderer),
  exit_(false)
{}

gamestates::GameStateName TestState::run()
{
    Keyboard keyboard = Keyboard();
    std::unique_ptr<Events> events(new Events());
    Universe universe = Universe(renderer_);
    CollisionDetector collision_detector = CollisionDetector();
    GameObjectMediator game_object_mediator(universe, collision_detector);

    keyboard.add_listener(this);
    events->add_listener(this);
    events->add_listener(&keyboard);
    universe.add_game_service(std::move(events));

    MissileLauncher test_launcher = MissileLauncher(Team::FRIENDLY, game_object_mediator);

    //Render red filled quad
    int x = 0;

    Delay delayer(false);
    for(;;)
    {
        if (x > SCREEN_WIDTH - 1) {
            x = 0;
        }
        x += 10;

        test_launcher.create_missile(x, SCREEN_WIDTH / 2, 0, -2.2);

        if(exit_){
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

gamestates::GameStateName TestState::name() const
{
	return gamestates::TEST;
}

void TestState::display_debug_frames_(Delay *delayer) {
    SDL_Surface *frame_rate_surface = delayer->grab_frame_rate();
    SDL_Texture *frame_rate_texture = SDL_CreateTextureFromSurface(renderer_, frame_rate_surface);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 70; // controls the height of the rect
    SDL_RenderCopy(renderer_, frame_rate_texture, NULL, &Message_rect);
    SDL_FreeSurface(frame_rate_surface);
}

/* listeners */

void TestState::handle_key_press(std::string keypress) {
    if (keypress == "ESC"){
        exit_ = true;
    }

    printf("Key returned was: %s\n", keypress.c_str());
}

void TestState::notify_events(SDL_Event e) {
    switch(e.type) {
        case SDL_QUIT:
            printf("SDL_QUIT was called!\n");
            exit_ = true;
            break;
    }
}

