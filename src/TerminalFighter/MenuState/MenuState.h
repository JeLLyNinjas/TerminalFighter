#pragma once

#include <SDL2/SDL.h>

#include "../Engine/GameState/I_GameState.h"
#include "../Engine/GraphicsHandler/GraphicsHandler.h"
#include "../Engine/Delay/Delay.h"
#include "../MainMenu/MainMenu.h"

#include "Settings/I_Settings.h"

class Delay;
struct SDL_Renderer;

class MenuState : public I_GameState {
public:
    MenuState(SDL_Renderer& renderer, const I_Settings& settings);
    ~MenuState();
    gamestates::GameStateName run();
    gamestates::GameStateName name() const;

private:
    void display_debug_frames(Delay* delayer);
    void render();
    SDL_Renderer& renderer_;
    const I_Settings& settings_;
};
