#pragma once
#include <SDL2/SDL.h>

#include <src/gamestates/I_Gamestate.h>

#include <src/MissileLauncher.h>
#include <src/GameConstants.h>
#include <src/KeyboardListener.h>
#include <src/Keyboard.h>
#include <src/Events.h>
#include <src/Delay.h>

class Delay;
class SDL_Renderer;

class TestState : public I_GameState, public KeyboardListener, public EventsListener {
public:
    TestState(SDL_Renderer& renderer);
    gamestates::GameStateName run();
    gamestates::GameStateName name() const;

    /* listeners */
    void handle_key_press(const std::string& keypress);
    void notify_events(const SDL_Event& e);

private:
    void display_debug_frames_(Delay* delayer);
    bool exit_;

    SDL_Renderer& renderer_;
};
