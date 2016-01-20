#pragma once 

#include <SDL.h>

namespace gamestates {
enum GameStateName { 
	MAIN_MENU, 
	OPENING_CUTSCENE, 
	LEVEL_1,
	EXIT,
	TEST
};	
}

class I_GameState {
public:
	virtual gamestates::GameStateName run(SDL_Renderer* renderer) = 0;
	virtual gamestates::GameStateName name() const = 0;
};
