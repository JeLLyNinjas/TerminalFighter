#include "game_object.h"

unsigned int GameObject::id_counter_ = 0;

GameObject::GameObject(){
    x_pos_ = 0;
    y_pos_ = 0;
    id_ = id_counter_++;
}

GameObject::GameObject(double x_pos, double y_pos)
    : x_pos_(x_pos)
    , y_pos_(y_pos)
    , id_(id_counter_++)
{ }

const double GameObject::x_pos() const {
    return x_pos_;
}

const double GameObject::y_pos() const {
    return y_pos_;
}

const int GameObject::id() const {
    return id_;
}

