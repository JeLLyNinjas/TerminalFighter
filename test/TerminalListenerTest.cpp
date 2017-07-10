#include <SDL2/SDL.h>
#include <tuple>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mocks/MockTerminalListener.h"
#include "../src/Terminal.h"

#include <SDL_ttf.h>
#include <string>

using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class TerminalListenerTest : public ::testing::Test {
public:
    MockTerminalListener* mock_terminal_listener_;
    Terminal* terminal_;

    virtual void SetUp() {
        mock_terminal_listener_ = new MockTerminalListener();
        terminal_ = new Terminal((100 / 2) - 400, 100 - 150, 100, 30);
        terminal_->Observable<TerminalListener>::add_listener(mock_terminal_listener_);
    }
    virtual void TearDown() {}

};

TEST_F(TerminalListenerTest, word_test) {
    terminal_->handle_key_press("Hi");
}
