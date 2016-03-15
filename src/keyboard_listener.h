#pragma once

#include <string>

class KeyboardListener{
public:
    virtual void notify_keyboard_key_pressed(std::string keypress) = 0;
};
