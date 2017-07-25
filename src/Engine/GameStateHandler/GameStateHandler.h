#pragma once
#include <vector>
#include <map>

#include <SDL.h>

#include "GameState/I_GameState.h"

class GameStateHandler {
public:
    GameStateHandler(std::vector<I_GameState*>& gamestates);
    void start(gamestates::GameStateName first_state);

private:
    std::map<gamestates::GameStateName, I_GameState*> gamestates_;
};
