#include <glog/logging.h>

#include "GameObject.h"

unsigned int GameObject::id_counter_ = 0;

GameObject::GameObject()
    : x_pos_(0)
    , y_pos_(0)
    , health_(1)
    , id_(id_counter_++) {
    x_pos_ = 0;
    y_pos_ = 0;
}

GameObject::GameObject(double x_pos, double y_pos, 
        double width, double height,
        double x_vel, double y_vel, 
        int health)
    : x_pos_(x_pos)
    , y_pos_(y_pos)
    , width_(width)
    , height_(height)
    , x_vel_(x_vel)
    , y_vel_(y_vel)
    , health_(health)
    , id_(id_counter_++) {
}

GameObject::~GameObject() {
    DLOG(INFO) << "GameObject with id: " << id_ << " died";
}

void GameObject::notify_destroyed() {
    for (DestroyedListener* listener : listeners_) {
        listener->object_destroyed(id_);
    }
}

void GameObject::take_damage(int damage) {
    health_ -= damage;

    if (health_ <= 0) {
        notify_destroyed();
    }
}

double GameObject::x_pos() const {
    return x_pos_;
}

double GameObject::y_pos() const {
    return y_pos_;
}

double GameObject::width() const {
    return width_;
}
double GameObject::height() const {
    return height_;
}

double GameObject::x_vel() const {
    return x_vel_;
}

double GameObject::y_vel() const {
    return y_vel_;
}

int GameObject::id() const {
    return id_;
}

