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

TEST_F(KeyboardListenerTest, test_key_esc) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("ESC"));
    sdlevent->key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_left) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("LEFT"));
    sdlevent->key.keysym.sym = SDLK_LEFT;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_right) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("RIGHT"));
    sdlevent->key.keysym.sym = SDLK_RIGHT;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_up) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("UP"));
    sdlevent->key.keysym.sym = SDLK_UP;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_down) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("DOWN"));
    sdlevent->key.keysym.sym = SDLK_DOWN;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_space) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("SPACE"));
    sdlevent->key.keysym.sym = SDLK_SPACE;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_backspace) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("BKSPACE"));
    sdlevent->key.keysym.sym = SDLK_BACKSPACE;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_slash) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("SLASH"));
    sdlevent->key.keysym.sym = SDLK_SLASH;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_enter) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("ENTER"));
    sdlevent->key.keysym.sym = SDLK_RETURN;
    SDL_PushEvent(sdlevent);
    events->update();
}


TEST_F(KeyboardListenerTest, test_key_a) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("a"));
    sdlevent->key.keysym.sym = SDLK_a;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_b) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("b"));
    sdlevent->key.keysym.sym = SDLK_b;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_c) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("c"));
    sdlevent->key.keysym.sym = SDLK_c;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_d) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("d"));
    sdlevent->key.keysym.sym = SDLK_d;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_e) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("e"));
    sdlevent->key.keysym.sym = SDLK_e;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_f) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("f"));
    sdlevent->key.keysym.sym = SDLK_f;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_g) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("g"));
    sdlevent->key.keysym.sym = SDLK_g;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_h) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("h"));
    sdlevent->key.keysym.sym = SDLK_h;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_i) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("i"));
    sdlevent->key.keysym.sym = SDLK_i;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_j) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("j"));
    sdlevent->key.keysym.sym = SDLK_j;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_k) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("k"));
    sdlevent->key.keysym.sym = SDLK_k;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_l) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("l"));
    sdlevent->key.keysym.sym = SDLK_l;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_m) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("m"));
    sdlevent->key.keysym.sym = SDLK_m;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_n) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("n"));
    sdlevent->key.keysym.sym = SDLK_n;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_o) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("o"));
    sdlevent->key.keysym.sym = SDLK_o;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_p) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("p"));
    sdlevent->key.keysym.sym = SDLK_p;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_q) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("q"));
    sdlevent->key.keysym.sym = SDLK_q;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_r) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("r"));
    sdlevent->key.keysym.sym = SDLK_r;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_s) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("s"));
    sdlevent->key.keysym.sym = SDLK_s;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_t) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("t"));
    sdlevent->key.keysym.sym = SDLK_t;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_u) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("u"));
    sdlevent->key.keysym.sym = SDLK_u;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_v) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("v"));
    sdlevent->key.keysym.sym = SDLK_v;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_w) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("w"));
    sdlevent->key.keysym.sym = SDLK_w;
    SDL_PushEvent(sdlevent);
    events->update();
}
TEST_F(KeyboardListenerTest, test_key_x) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("x"));
    sdlevent->key.keysym.sym = SDLK_x;
    SDL_PushEvent(sdlevent);
    events->update();
}
TEST_F(KeyboardListenerTest, test_key_y) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("y"));
    sdlevent->key.keysym.sym = SDLK_y;
    SDL_PushEvent(sdlevent);
    events->update();
}

TEST_F(KeyboardListenerTest, test_key_z) {
    EXPECT_CALL(*keyboard_listener, notify_keyboard_key_pressed("z"));
    sdlevent->key.keysym.sym = SDLK_z;
    SDL_PushEvent(sdlevent);
    events->update();
}
