#include "gmock/gmock.h"

#include "../../src/Engine/I_Gamestate.h"

class MockGameState : public I_GameState {
public:
    MOCK_METHOD0(run, gamestates::GameStateName());
    MOCK_CONST_METHOD0(name, gamestates::GameStateName());
};
