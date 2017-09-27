#pragma once

#include <SDL2/SDL.h>

#include "../Engine/GameState/I_GameState.h"
#include "../Engine/Delay/Delay.h"

class Delay;
struct SDL_Renderer;

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
