#pragma once
#include <SDL2/SDL.h>


class Game_Object {

public:
    Game_Object(double x_vel, double y_vel, double x_pos, double y_pos) {
        x_velocity_ = x_vel;
        y_velocity_ = y_vel;
        x_position_ = x_pos;
        y_position_ = y_pos;
    }

    virtual void update() = 0;
    virtual double return_x_velocity() = 0;
    virtual double return_y_velocity() = 0;
    virtual double return_x_position() = 0;
    virtual double return_y_position() = 0;

protected:
    double x_velocity_, y_velocity_;
    double x_position_, y_position_;

};
