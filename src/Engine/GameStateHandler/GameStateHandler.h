#pragma once
#include <vector>
#include <map>

#include <SDL.h>

#include "GameState/I_GameState.h"

/**
 * The GameStateHandler is the top level object for handling game flow.
 * Each GameState contains internal logic on what happens in each GameState.
 * The GameStateHandler just runs them, takes their return value and runs the next GameState.
 */
class GameStateHandler {
public:
	/**
	 * @param gamestates is a vector of GameStates (inheriting I_GameState)
	 * This must be a complete list of GameStates that will be run for the duration of execution.
	 */
    GameStateHandler(std::vector<I_GameState*>& gamestates);

    /**
     * Runs all the gamestates. Conceptaully, this function should only exit when the game is exited.
     * @param first_state defines which state is executed first.
     */
    void start(gamestates::GameStateName first_state);

private:
    std::map<gamestates::GameStateName, I_GameState*> gamestates_;
};
