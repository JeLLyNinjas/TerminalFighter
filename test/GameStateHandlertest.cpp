#include <map>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/Engine/GamestateHandler.h"
#include "mocks/MockGameState.h"

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

TEST(GameStateHandlerTest, runs_gamestate) {
    MockGameState* mock_mainmenu = new MockGameState();
    EXPECT_CALL(*mock_mainmenu, name())
    .WillRepeatedly(Return(gamestates::MAIN_MENU));
    EXPECT_CALL(*mock_mainmenu, run())
    .WillOnce(Return(gamestates::EXIT));
    std::vector<I_GameState*> gamestates;
    gamestates.push_back(mock_mainmenu);
    GameStateHandler gs_handler = GameStateHandler(gamestates);
    gs_handler.start(gamestates::MAIN_MENU);
    delete mock_mainmenu;
}

TEST(GameStateHandlerTest, runs_next_gamestate) {
    MockGameState* mock_opening = new MockGameState();
    EXPECT_CALL(*mock_opening, name())
    .WillRepeatedly(Return(gamestates::OPENING_CUTSCENE));
    MockGameState* mock_mainmenu = new MockGameState();
    EXPECT_CALL(*mock_mainmenu, name())
    .WillRepeatedly(Return(gamestates::MAIN_MENU));
    {
        InSequence dummy;
        EXPECT_CALL(*mock_opening, run())
        .WillOnce(Return(gamestates::MAIN_MENU));
        EXPECT_CALL(*mock_mainmenu, run())
        .WillOnce(Return(gamestates::EXIT));
    }
    std::vector<I_GameState*> gamestates;
    gamestates.push_back(mock_mainmenu);
    gamestates.push_back(mock_opening);
    GameStateHandler gs_handler = GameStateHandler(gamestates);
    gs_handler.start(gamestates::OPENING_CUTSCENE);
    delete mock_opening;
    delete mock_mainmenu;
}
