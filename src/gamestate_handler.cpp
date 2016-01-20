#include "gamestate_handler.h"

GameStateHandler::GameStateHandler(std::map<gamestates::GameStateName, I_GameState*>* gamestates)
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
    std::map<gamestates::GameStateName, I_GameState*>::iterator it; 
    while(next_state != gamestates::EXIT){
        it = gamestates_->find(next_state);
        SDL_assert(it != gamestates_->end());
        if(next_state == gamestates::EXIT){
            return;
        }
        next_state = it->second->run(renderer_);
    }
}
