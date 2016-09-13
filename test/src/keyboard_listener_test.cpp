#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_constants.h"
#include "missile_launcher.h"
#include "mocks/mock_keyboard_listener.h"
#include "keyboard.h"
#include "events.h"
#include <SDL2/SDL.h>

using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class KeyboardListenerTest : public ::testing::Test {
public: 
    MockKeyboardListener* keyboard_listener;
    Keyboard* keyboard;
    Events* events;

    virtual void SetUp() {
        keyboard_listener = new MockKeyboardListener();
        keyboard = new Keyboard();
        events = new Events();
        
        keyboard->add_listener(keyboard_listener);
        events->add_listener(keyboard);
    }

    virtual void TearDown() {
        delete keyboard_listener;
        delete keyboard;
        delete events;
    }

};

TEST_F(KeyboardListenerTest, test_key_a) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed(_));

    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    sdlevent.key.keysym.sym = SDLK_a;

    SDL_PushEvent(&sdlevent);
    events->update();
}
