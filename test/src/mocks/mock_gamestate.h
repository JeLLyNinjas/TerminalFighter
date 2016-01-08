#include "gmock/gmock.h"

#include "I_gamestate.h"

class MockGameState : public I_GameState {
public:
	MOCK_METHOD1(run, GameStateName(SDL_Renderer* renderer));
	MOCK_CONST_METHOD0(name, GameStateName());  
};
