#include "gmock/gmock.h"

#include "game_constants.h"
#include "keyboard_listener.h"

class MockKeyboardListener : public KeyboardListener{
public:
    MOCK_METHOD1(notify_keyboard_key_pressed, void(std::string keypress));
};
