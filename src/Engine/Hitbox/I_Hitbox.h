#pragma once

#include <SDL2/SDL.h>

#include "Rect/Rect.h"

struct Circle {
    double x, y;
    double r;
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
    virtual void set_pos(double x, double y) = 0;
    virtual const Rect& hitbox() const = 0;
    virtual const Circle& hitbox_circle() const = 0;
    virtual const Shape::Shape& hitbox_type() const = 0;
};
