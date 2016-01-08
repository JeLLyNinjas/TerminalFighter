#pragma once 
#include <map>

#include <SDL.h>
#include "game_constants.h"
#include "I_gamestate.h"

class GameStateHandler {
public:
	GameStateHandler(std::map<GameStateName, I_GameState*>* gamestates);
	void set_renderer(SDL_Renderer* renderer);
	void set_window(SDL_Window* window);
	void start(GameStateName first_state);

private:
	std::map<GameStateName, I_GameState*>* gamestates_;
	SDL_Renderer* renderer_;
	SDL_Window* window_;
};