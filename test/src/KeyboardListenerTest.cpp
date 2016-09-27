#include <SDL2/SDL.h>
#include <tuple>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MissileLauncher.h"
#include "mocks/MockKeyboardListener.h"
#include "Keyboard.h"
#include "Events.h"


using ::testing::_;
using ::testing::Property;
using ::testing::InSequence;

class KeyboardListenerTest : public ::testing::TestWithParam<std::tuple<std::string , int>> {
public:
    MockKeyboardListener* mock_keyboard_listener_;
    Keyboard* keyboard_;
    Events* events_;
    SDL_Event* sdl_event_;

    virtual void SetUp() {
        mock_keyboard_listener_ = new MockKeyboardListener();
        keyboard_ = new Keyboard();
        events_ = new Events();
        sdl_event_ = new SDL_Event();
        sdl_event_->type = SDL_KEYDOWN;
        keyboard_->add_listener(mock_keyboard_listener_);
        events_->add_listener(keyboard_);
    }

    virtual void TearDown() {
        delete mock_keyboard_listener_;
        delete keyboard_;
        delete events_;
    }

};


INSTANTIATE_TEST_CASE_P(testKeys,
                        KeyboardListenerTest,
                        ::testing::Values(std::make_tuple("a", SDLK_a),
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
                                std::make_tuple("0", SDLK_0),
                                std::make_tuple("1", SDLK_1),
                                std::make_tuple("2", SDLK_2),
                                std::make_tuple("3", SDLK_3),
                                std::make_tuple("4", SDLK_4),
                                std::make_tuple("5", SDLK_5),
                                std::make_tuple("6", SDLK_6),
                                std::make_tuple("7", SDLK_7),
                                std::make_tuple("8", SDLK_8),
                                std::make_tuple("9", SDLK_9),
                                std::make_tuple("ESC", SDLK_ESCAPE),
                                std::make_tuple("LEFT", SDLK_LEFT),
                                std::make_tuple("RIGHT", SDLK_RIGHT),
                                std::make_tuple("UP", SDLK_UP),
                                std::make_tuple("DOWN", SDLK_DOWN),
                                std::make_tuple(" ", SDLK_SPACE),
                                std::make_tuple("BKSPACE", SDLK_BACKSPACE),
                                std::make_tuple("/", SDLK_SLASH),
                                std::make_tuple("\n", SDLK_RETURN)
                                         ));

TEST_P(KeyboardListenerTest, testAllKeys) {
    EXPECT_CALL(*mock_keyboard_listener_, handle_key_press(std::get<0>(GetParam())));
    sdl_event_->key.keysym.sym = std::get<1>(GetParam());
    SDL_PushEvent(sdl_event_);
    events_->update();
}


