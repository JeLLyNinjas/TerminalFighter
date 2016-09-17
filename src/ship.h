#pragma once

#include <vector>

#include "game_object.h"
#include "hitbox.h"

class Ship : public GameObject {
    public:
        Ship(double x_pos, double y_pos, double x_vel, double y_vel)
            : GameObject(x_pos, y_pos)
              , x_vel_(x_vel)
              , y_vel_(y_vel)
    { }

        virtual void update() = 0;
        virtual void draw(GraphicsHandler *graphics) = 0;
        virtual double x_vel() { return x_vel_; }
        virtual double y_vel() { return y_vel_; }
        virtual void notify_collision(Ship* collided_ship, int hitbox_number);
        virtual std::vector<Hitbox> get_hitboxes() = 0;

    protected:
        double x_vel_;
        double y_vel_;
};
