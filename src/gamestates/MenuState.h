#pragma once

#include <SDL2/SDL.h>

#include "I_Gamestate.h"

#include "../Engine/Delay.h"

class Delay;
class SDL_Renderer;

class MenuState : public I_GameState {
public:
    MenuState(SDL_Renderer& renderer);
    ~MenuState();
    gamestates::GameStateName run();
    gamestates::GameStateName name() const;

private:
    void display_debug_frames(Delay* delayer);
    SDL_Renderer& renderer_;
};
