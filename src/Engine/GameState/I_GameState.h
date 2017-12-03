#pragma once

/**
 * Many objects are intended to inherit I_GameState.
 * This is the top level type in the Terminal Fighter Engine for handling game flow.
 * This interface allows for GameStateHandler to manage various GameStates.
 * Each GameState individually decides what to do in each state,
 * and what state to go to next.
 */

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
    virtual ~I_GameState() {}

    /**
     * Normally should run an infinite loop which draws to screen and is interactable.
     * @return returns the next GameState to execute.
     */
    virtual gamestates::GameStateName run() = 0;

    /**
     * @returns returns it's own GameState from the GameStateName enum
     * The return value should be unique for every unique GameState.
     */
    virtual gamestates::GameStateName name() const = 0;
};
