#include <iostream>

#include "GamestateHandler.h"

GameStateHandler::GameStateHandler(std::vector<I_GameState*>& gamestates) {
    gamestates_ = std::map<gamestates::GameStateName, I_GameState*>();

    for (auto const& state : gamestates) {
        (gamestates_)[state->name()] = state;
    }
}

void GameStateHandler::start(gamestates::GameStateName first_state) {
    gamestates::GameStateName next_state = first_state;

    for (;;) {
        if (next_state == gamestates::EXIT) {
            return;
        }

        if (gamestates_.count(next_state) == 0) {
            exit(1);
        }

        next_state = (gamestates_)[next_state]->run();
    }
}
