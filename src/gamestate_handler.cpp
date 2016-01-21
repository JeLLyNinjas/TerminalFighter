#include "gamestate_handler.h"
#include <iostream>

GameStateHandler::GameStateHandler(std::map<gamestates::GameStateName, I_GameState*> &gamestates)
    : gamestates_(gamestates)
    , window_(NULL)
    , renderer_(NULL)
{ }

void GameStateHandler::start(gamestates::GameStateName first_state){
    gamestates::GameStateName next_state = first_state;
    for(;;){
        if(next_state == gamestates::EXIT){
            return;
        }
        if(gamestates_.count(next_state) == 0){
            std::cout << "Gamestate " << next_state << " non-existent!" << std::endl;
            exit(1);
        }
        next_state = gamestates_[next_state]->run(renderer_);
    }
}
