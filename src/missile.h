#pragma once
#include <string>

class Missile {
public:
    Missile(std::string missile_name);
    
    std::string print_name();

private:
    std::string name;
};
