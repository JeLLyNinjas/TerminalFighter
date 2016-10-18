#pragma once

#include <SDL2/SDL.h>

struct Circle {
    int x, y;
    int r;
};

namespace Shape {
    enum Shape {
        RECT,
        CIRCLE
    };
}

class I_Hitbox {
public:
    virtual bool is_overlapping(const I_Hitbox& other_hitbox) const = 0;
    virtual void set_pos(int x, int y) = 0;
    virtual const SDL_Rect& hitbox() const = 0;
    virtual const Circle& hitbox_circle() const = 0;
    virtual const Shape::Shape& hitbox_type() const = 0;
};
