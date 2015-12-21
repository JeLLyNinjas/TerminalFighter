#include "missile.h"

Missile::Missile(std::string missile_name) {
    name = missile_name;
}

std::string Missile::print_name() {
    return name;
}
