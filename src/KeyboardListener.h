#pragma once

#include <string>

class KeyboardListener {
public:
    virtual void handle_key_press(const std::string& keypress) = 0;
};
