#include "test_state.h"
#include "game_constants.h"
#include "delay.h"
#include "universe.h"
#include "missile_launcher.h"
#include "missile.h"

TestState::TestState(SDL_Renderer* renderer)
: renderer_(renderer)
{}

TestState:: ~TestState() {}


gamestates::GameStateName TestState::run()
{
    Universe universe(renderer_);
    MissileLauncher test_launcher = MissileLauncher(FRIENDLY);
    test_launcher.add_listener(&universe);

    int x = 0;

    Delay delayer(false);
    for(;;)
    {
        if (x > SCREEN_WIDTH - 1)
            x = 0; x += 10;

        test_launcher.create_missile(x, SCREEN_WIDTH / 2, 0, -2.2);

        if(!process_events()){
        	return gamestates::EXIT;
        }
        universe.update_all();
        universe.draw_all();

        display_debug_frames(&delayer);

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

void TestState::display_debug_frames(Delay *delayer) {
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

bool TestState::process_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            printf("SDL_QUIT was called\n");
            return false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                printf("Esc was Pressed!\n");
                return false;
                break;
            case SDLK_LEFT:
                printf("Left arrow was Pressed!\n");
                break;
            case SDLK_RIGHT:
                printf("Right arrow was Pressed!\n");
                break;
            case SDLK_UP:
                break;
            case SDLK_DOWN:
                break;
            case SDLK_SPACE:
                printf("Space was pressed!\n");
            }
        }
    }
    return true;
}

