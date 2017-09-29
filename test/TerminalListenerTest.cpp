#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "mocks/MockTerminalListener.h"
#include "../src/TerminalFighter/Terminal/Terminal.h"


using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class TerminalListenerTest : public ::testing::Test {
public:
    MockTerminalListener mock_terminal_listener_;
    Terminal* terminal_;

    virtual void SetUp() {
        terminal_ = new Terminal((100 / 2) - 400, 100 - 150, 100, 30, "");
        terminal_->Observable<TerminalListener>::add_listener(&mock_terminal_listener_);
    }
    virtual void TearDown() {}

};

TEST_F(TerminalListenerTest, single_call) {
    EXPECT_CALL(mock_terminal_listener_, handle_input("hi")).Times(1);
    terminal_->handle_key_press("h");
    terminal_->handle_key_press("i");
    terminal_->handle_key_press("ENTER");
}

TEST_F(TerminalListenerTest, multi_empty_call) {
    EXPECT_CALL(mock_terminal_listener_, handle_input("")).Times(3);
    terminal_->handle_key_press("ENTER");
    terminal_->handle_key_press("ENTER");
    terminal_->handle_key_press("ENTER");
}

TEST_F(TerminalListenerTest, empty_string) {
    EXPECT_CALL(mock_terminal_listener_, handle_input("")).Times(1);
    terminal_->handle_key_press("h");
    terminal_->handle_key_press("i");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("ENTER");
}

TEST_F(TerminalListenerTest, spam_bkspace_string) {
    EXPECT_CALL(mock_terminal_listener_, handle_input("")).Times(1);
    terminal_->handle_key_press("h");
    terminal_->handle_key_press("i");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("ENTER");
}

TEST_F(TerminalListenerTest, big_test_string) {
    EXPECT_CALL(mock_terminal_listener_, handle_input("abde135")).Times(1);
    terminal_->handle_key_press("a");
    terminal_->handle_key_press("b");
    terminal_->handle_key_press("c");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("d");
    terminal_->handle_key_press("e");
    terminal_->handle_key_press("1");
    terminal_->handle_key_press("2");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("3");
    terminal_->handle_key_press("4");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("5");
    terminal_->handle_key_press("ENTER");
    EXPECT_CALL(mock_terminal_listener_, handle_input("abc")).Times(1);
    terminal_->handle_key_press("a");
    terminal_->handle_key_press("b");
    terminal_->handle_key_press("c");
    terminal_->handle_key_press("d");
    terminal_->handle_key_press("BKSPACE");
    terminal_->handle_key_press("ENTER");
}
