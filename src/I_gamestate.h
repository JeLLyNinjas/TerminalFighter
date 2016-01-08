#pragma once 

#include <SDL.h>
#include "game_constants.h"

class I_GameState {
public:
	virtual GameStateName run(SDL_Renderer* renderer) = 0;
	virtual GameStateName name() const = 0;
};