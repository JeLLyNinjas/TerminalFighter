#pragma once
#include <SDL2/SDL.h>
#include "graphics_handler.h"

class GameObject {

public:
    GameObject(double x_pos, double y_pos);

    virtual void update() = 0;
    virtual void draw(GraphicsHandler *graphics) = 0;
    double x_pos();
    double y_pos();
    int id();

protected:
    double x_pos_;
    double y_pos_;
    unsigned int id_;

private:
    static unsigned int id_counter_;
};

