#include "gmock/gmock.h"

#include "../../src/Engine/GameState/I_GameState.h"

class MockGameState : public I_GameState {
public:
    MOCK_METHOD0(run, gamestates::GameStateName());
    MOCK_CONST_METHOD0(name, gamestates::GameStateName());
};
