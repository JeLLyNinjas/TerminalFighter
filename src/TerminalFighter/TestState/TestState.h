#pragma once
#include <SDL2/SDL.h>

#include "GameState/I_GameState.h"

#include "Keyboard/KeyboardListener.h"
#include "Keyboard/Keyboard.h"
#include "Events/Events.h"
#include "Delay/Delay.h"

#include "MissileLauncher/MissileLauncher.h"

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
