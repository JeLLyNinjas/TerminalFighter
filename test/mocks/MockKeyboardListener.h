#include "gmock/gmock.h"

#include "../../src/KeyboardListener.h"

class MockKeyboardListener : public KeyboardListener {
public:
    MOCK_METHOD1(handle_key_press, void(const std::string&));
};
