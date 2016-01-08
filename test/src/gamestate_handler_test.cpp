#include <map>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gamestate_handler.h"
#include "mocks/mock_gamestate.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

class GraphicsHandlerTest : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};

TEST(GameStateHandlerTest, runs_gamestate){
    MockGameState* mock_mainmenu = new MockGameState();
    EXPECT_CALL(*mock_mainmenu, run(_))
        .WillOnce(Return(EXIT));

    std::map<GameStateName, I_GameState*> gamestates;
    gamestates.insert(std::pair<GameStateName, I_GameState*>(MAIN_MENU, mock_mainmenu));
    
    GameStateHandler gs_handler = GameStateHandler(&gamestates);
    gs_handler.start(MAIN_MENU);

    delete mock_mainmenu;
}

TEST(GameStateHandlerTest, runs_next_gamestate) {
    InSequence dummy;

    MockGameState* mock_opening = new MockGameState();
    MockGameState* mock_mainmenu = new MockGameState();

    EXPECT_CALL(*mock_opening, run(_))
        .WillOnce(Return(MAIN_MENU));
    EXPECT_CALL(*mock_mainmenu, run(_))
        .WillOnce(Return(EXIT));    
    
    std::map<GameStateName, I_GameState*> gamestates;
    gamestates.insert(std::pair<GameStateName, I_GameState*>(OPENING_CUTSCENE, mock_opening));
    gamestates.insert(std::pair<GameStateName, I_GameState*>(MAIN_MENU, mock_mainmenu));
    
    GameStateHandler gs_handler = GameStateHandler(&gamestates);
    gs_handler.start(OPENING_CUTSCENE);

    delete mock_opening;
    delete mock_mainmenu;
}

