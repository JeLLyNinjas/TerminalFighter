#pragma once 
#include <map>

#include <SDL.h>
#include "I_gamestate.h"

class GameStateHandler {
public:
	GameStateHandler(std::map<gamestates::GameStateName, I_GameState*> &gamestates);
	void start(gamestates::GameStateName first_state);

private:
	std::map<gamestates::GameStateName, I_GameState*>& gamestates_;
	SDL_Renderer* renderer_;
	SDL_Window* window_;
};