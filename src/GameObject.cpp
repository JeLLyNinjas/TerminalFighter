#include "GameObject.h"

unsigned int GameObject::id_counter_ = 0;

GameObject::GameObject() {
    x_pos_ = 0;
    y_pos_ = 0;
    id_ = id_counter_++;
}

GameObject::GameObject(double x_pos, double y_pos, double x_vel, double y_vel)
    : x_pos_(x_pos)
    , y_pos_(y_pos)
    , x_vel_(x_vel)
    , y_vel_(y_vel)
    , id_(id_counter_++)
{ }

double GameObject::x_pos() const {
    return x_pos_;
}

double GameObject::y_pos() const {
    return y_pos_;
}

double GameObject::x_vel() const
{
    return x_vel_;
}

double GameObject::y_vel() const
{
    return y_vel_;
}

int GameObject::id() const {
    return id_;
}

