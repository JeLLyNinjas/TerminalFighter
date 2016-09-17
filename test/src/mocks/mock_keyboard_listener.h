#include "gmock/gmock.h"

#include "game_constants.h"
#include "keyboard_listener.h"

class MockKeyboardListener : public KeyboardListener{
public:
    MOCK_METHOD1(handle_key_press, void(std::string keypress));
};
