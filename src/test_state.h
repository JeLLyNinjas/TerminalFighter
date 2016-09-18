#pragma once

#include <SDL2/SDL.h>
#include "I_gamestate.h"
#include "game_constants.h"
#include "delay.h"
#include "universe.h"
#include "missile_launcher.h"
#include "missile.h"

class Delay;
class SDL_Renderer;

class TestState : public I_GameState {
public:
	TestState(SDL_Renderer* renderer);
    ~TestState();
	gamestates::GameStateName run();
	gamestates::GameStateName name() const;

private:
	void display_debug_frames(Delay *delayer);
	bool process_events();

	SDL_Renderer* renderer_;
};
