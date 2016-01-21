#include "gamestate_handler.h"

GameStateHandler::GameStateHandler(std::map<gamestates::GameStateName, I_GameState*> &gamestates)
    : gamestates_(gamestates)
    , window_(NULL)
    , renderer_(NULL)
{ }

void GameStateHandler::set_renderer(SDL_Renderer* renderer) {
    renderer_ = renderer;
}

void GameStateHandler::set_window(SDL_Window* window) {
    window_ = window;
}

void GameStateHandler::start(gamestates::GameStateName first_state){
    gamestates::GameStateName next_state = first_state;
    for(;;){
        if(next_state == gamestates::EXIT){
            return;
        }
        next_state = gamestates_[next_state]->run(renderer_);
    }
}
