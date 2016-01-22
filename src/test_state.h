#pragma once

#include "I_gamestate.h"

class Delay;
class SDL_Renderer;

class TestState : public I_GameState {
public:
	TestState(SDL_Renderer* renderer);
	gamestates::GameStateName run();
	gamestates::GameStateName name() const;

private:
	void display_debug_frames(Delay *delayer);
	bool process_events();

	SDL_Renderer* renderer_;
};
