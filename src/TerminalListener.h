#pragma once

class TerminalListener {
public:
    virtual void handle_input(const std::string& input) = 0;
};
