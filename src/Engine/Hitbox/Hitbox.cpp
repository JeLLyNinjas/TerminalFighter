#include "Hitbox.h"

Hitbox::Hitbox(int x_pos, int y_pos, int width, int height)
    : hitbox_type_(Shape::RECT),
      hitbox_ {x_pos, y_pos, width, height} {
}

Hitbox::Hitbox(int x_pos, int y_pos, int radius)
    : hitbox_type_(Shape::CIRCLE) {
    circle_hitbox_.x = x_pos;
    circle_hitbox_.y = y_pos;
    circle_hitbox_.r = radius;
}

Hitbox::Hitbox(SDL_Rect hitbox)
    : hitbox_(hitbox),
      hitbox_type_(Shape::RECT) {
}

Hitbox::Hitbox(Circle hitbox)
    : circle_hitbox_(hitbox),
      hitbox_type_(Shape::CIRCLE) {
}

void Hitbox::set_pos(int x, int y) {
    if (hitbox_type_ == Shape::RECT) {
        hitbox_.x = x;
        hitbox_.y = y;
    } else {
        circle_hitbox_.x = x;
        circle_hitbox_.y = y;
    }
}

bool Hitbox::is_overlapping(const I_Hitbox& other_hitbox) const {
    bool is_overlapping = false;

    if (this->hitbox_type() == Shape::CIRCLE && other_hitbox.hitbox_type() == Shape::CIRCLE) {
        // CHECK COLLISION BETWEEN CIRCLES
        is_overlapping = check_overlap(this->circle_hitbox_, other_hitbox.hitbox_circle());
    } else if (this->hitbox_type() == Shape::RECT && other_hitbox.hitbox_type() == Shape::RECT) {
        // CHECKS COLLISION BETWEEN RECTS
        is_overlapping = check_overlap(this->hitbox_, other_hitbox.hitbox());
    } else if (this->hitbox_type() == Shape::CIRCLE && other_hitbox.hitbox_type() == Shape::RECT) {
        // CHECKS COLLISION BETWEEN CIRCLE AND RECT
        is_overlapping = check_overlap(this->circle_hitbox_, other_hitbox.hitbox());
    } else {
        // CHECKS COLLISION BETWEEN RECT AND CIRCLE
        is_overlapping = check_overlap(other_hitbox.hitbox_circle(), this->hitbox_);
    }

    return is_overlapping;
}

bool Hitbox::check_overlap(const Circle& hitbox, const Circle& other_hitbox) const {
    double radiusSquared = hitbox.r + other_hitbox.r;
    radiusSquared = radiusSquared * radiusSquared;
    double delta_x = hitbox.x - other_hitbox.x;
    double delta_y = hitbox.y - other_hitbox.y;
    double distanceSquared = delta_x * delta_x + delta_y * delta_y;
    return distanceSquared <= radiusSquared;
}

bool Hitbox::check_overlap(const Circle& hitbox, const SDL_Rect& other_hitbox) const {
    double rect_centre_x = (other_hitbox.x + other_hitbox.w) / 2;
    double rect_centre_y = (other_hitbox.y + other_hitbox.h) / 2;
    double distance_x = abs(hitbox.x - rect_centre_x);
    double distance_y = abs(hitbox.y - rect_centre_y);

    if (distance_x > (other_hitbox.w / 2 + hitbox.r)) {
        return false;
    }

    if (distance_y > (other_hitbox.h / 2 + hitbox.r)) {
        return false;
    }

    if (distance_x <= (other_hitbox.w / 2)) {
        return true;
    }

    if (distance_y <= (other_hitbox.h / 2)) {
        return true;
    }

    double d_x = (distance_x - other_hitbox.w / 2);
    double d_y = (distance_y - other_hitbox.h / 2);
    double cornerDistance_sq = (d_x * d_x) + (d_y * d_y);
    return (cornerDistance_sq <= (hitbox.r * hitbox.r));
}

bool Hitbox::check_overlap(const SDL_Rect& hitbox, const SDL_Rect& other_hitbox) const {
    return SDL_HasIntersection(&hitbox_, &other_hitbox);
}

const Shape::Shape& Hitbox::hitbox_type() const {
    return hitbox_type_;
}

const SDL_Rect& Hitbox::hitbox() const {
    return hitbox_;
}

const Circle& Hitbox::hitbox_circle() const {
    return circle_hitbox_;
}
