#pragma once
#include <SDL2/SDL.h>

#include "graphics_handler.h"

class GameObject {

public:
    GameObject();
    GameObject(double x_pos, double y_pos);

    virtual void update() = 0;
    virtual void draw(GraphicsHandler *graphics) = 0;
    const double x_pos() const;
    const double y_pos() const;
    const int id() const;

protected:
    double x_pos_;
    double y_pos_;
    unsigned int id_;

private:
    static unsigned int id_counter_;
};

