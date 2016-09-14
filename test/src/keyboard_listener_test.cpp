#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game_constants.h"
#include "missile_launcher.h"
#include "mocks/mock_keyboard_listener.h"
#include "keyboard.h"
#include "events.h"

#include <SDL2/SDL.h>
#include <tuple>

using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class KeyboardListenerTest : public ::testing::TestWithParam<std::tuple<std::string , int>> {
public: 
    MockKeyboardListener *keyboard_listener;
    Keyboard             *keyboard;
    Events               *events;
    SDL_Event            *sdlevent;

    virtual void SetUp() {
        keyboard_listener = new MockKeyboardListener();
        keyboard = new Keyboard();
        events = new Events();
        sdlevent = new SDL_Event();
        sdlevent->type = SDL_KEYDOWN;
        
        keyboard->add_listener(keyboard_listener);
        events->add_listener(keyboard);
    }

    virtual void TearDown() {
        delete keyboard_listener;
        delete keyboard;
        delete events;
    }

};


INSTANTIATE_TEST_CASE_P(testKeys,
                        KeyboardListenerTest,
                        ::testing::Values(std::make_tuple("a",SDLK_a),
                            std::make_tuple("b", SDLK_b),
                            std::make_tuple("c", SDLK_c),
                            std::make_tuple("d", SDLK_d),
                            std::make_tuple("e", SDLK_e),
                            std::make_tuple("f", SDLK_f),
                            std::make_tuple("g", SDLK_g),
                            std::make_tuple("h", SDLK_h),
                            std::make_tuple("i", SDLK_i),
                            std::make_tuple("j", SDLK_j),
                            std::make_tuple("k", SDLK_k),
                            std::make_tuple("l", SDLK_l),
                            std::make_tuple("m", SDLK_m),
                            std::make_tuple("n", SDLK_n),
                            std::make_tuple("o", SDLK_o),
                            std::make_tuple("p", SDLK_p),
                            std::make_tuple("q", SDLK_q),
                            std::make_tuple("r", SDLK_r),
                            std::make_tuple("s", SDLK_s),
                            std::make_tuple("t", SDLK_t),
                            std::make_tuple("u", SDLK_u),
                            std::make_tuple("v", SDLK_v),
                            std::make_tuple("w", SDLK_w),
                            std::make_tuple("x", SDLK_x),
                            std::make_tuple("y", SDLK_y),
                            std::make_tuple("z", SDLK_z),
                            std::make_tuple("ESC", SDLK_ESCAPE),
                            std::make_tuple("LEFT", SDLK_LEFT),
                            std::make_tuple("RIGHT", SDLK_RIGHT),
                            std::make_tuple("UP", SDLK_UP),
                            std::make_tuple("DOWN", SDLK_DOWN),
                            std::make_tuple("SPACE", SDLK_SPACE),
                            std::make_tuple("BKSPACE", SDLK_BACKSPACE),
                            std::make_tuple("SLASH", SDLK_SLASH),
                            std::make_tuple("ENTER", SDLK_RETURN)
                        ));

TEST_P(KeyboardListenerTest, testAllKeys)
{
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed(std::get<0>(GetParam())));

    sdlevent->key.keysym.sym = std::get<1>(GetParam());
    SDL_PushEvent(sdlevent);
    events->update();
}


