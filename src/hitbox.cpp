#include "hitbox.h"

Hitbox::Hitbox(double x_pos, double y_pos, double width, double height) {
    hitbox_.x = x_pos;
    hitbox_.y = y_pos;
    hitbox_.w = width;
    hitbox_.h = height;

    hitbox_type_ = rect;
}

Hitbox::Hitbox(double x_pos, double y_pos, double radius) {
    circle_hitbox_.x = x_pos;
    circle_hitbox_.y = y_pos;
    circle_hitbox_.r = radius;

    hitbox_type_ = circle;
}

Hitbox::Hitbox(SDL_Rect hitbox) {
    hitbox_ = hitbox;
}

Hitbox::Hitbox(Circle hitbox) {
    circle_hitbox_ = hitbox;
}


bool Hitbox::is_overlapping(Hitbox& other_hitbox) {
    bool is_overlapping;

    // CHECK COLLISION BETWEEN CIRCLES
    if (*(this->hitbox_type()) == circle && *(other_hitbox.hitbox_type()) == circle)
        is_overlapping = check_overlap(this->circle_hitbox_, other_hitbox.circle_hitbox_);
    // CHECKS COLLISION BETWEEN RECTS
    else if (*(this->hitbox_type()) == rect && *(other_hitbox.hitbox_type()) == rect)
        is_overlapping = check_overlap(this->hitbox_, other_hitbox.hitbox_);
    // CHECKS COLLISION BETWEEN CIRCLE AND RECT
    else if (*(this->hitbox_type()) == circle && *(other_hitbox.hitbox_type()) == rect)
        is_overlapping = check_overlap(this->circle_hitbox_, other_hitbox.hitbox_);
    // CHECKS COLLISION BETWEEN RECT AND CIRCLE
    else if (*(this->hitbox_type()) == rect && *(other_hitbox.hitbox_type()) == circle)
        is_overlapping = check_overlap(other_hitbox.circle_hitbox_, this->hitbox_);

    return is_overlapping;
}

bool Hitbox::check_overlap(Circle& hitbox, Circle& other_hitbox)
{
    double radiusSquared = hitbox.r + other_hitbox.r;
    radiusSquared = radiusSquared * radiusSquared;

    double delta_x = hitbox.x - other_hitbox.x;
    double delta_y = hitbox.y - other_hitbox.y;
    double distanceSquared = delta_x * delta_x + delta_y * delta_y;

    if (distanceSquared <= radiusSquared)
    {
        return true;
    }

    return false;
}

bool Hitbox::check_overlap(Circle &hitbox, SDL_Rect &other_hitbox)
{
    double rect_centre_x = (other_hitbox.x + other_hitbox.w) / 2;
    double rect_centre_y = (other_hitbox.y + other_hitbox.h) / 2;

    double distance_x = abs(hitbox.x - rect_centre_x);
    double distance_y = abs(hitbox.y - rect_centre_y);

    if (distance_x > (other_hitbox.w / 2 + hitbox.r))
        return false;

    if (distance_y > (other_hitbox.h / 2 + hitbox.r))
        return false;

    if (distance_x <= (other_hitbox.w / 2))
        return true;

    if (distance_y <= (other_hitbox.h / 2))
        return true;

    double d_x = (distance_x - other_hitbox.w / 2);
    d_x = d_x * d_x;
    double d_y = (distance_y - other_hitbox.h / 2);
    d_y = d_y * d_y;

    double cornerDistance_sq = d_x + d_y;

    return (cornerDistance_sq <= (hitbox.r * hitbox.r));
}

bool Hitbox::check_overlap(SDL_Rect &hitbox, SDL_Rect &other_hitbox)
{
    return SDL_HasIntersection(&hitbox_, &other_hitbox);
}

const Shape* Hitbox::hitbox_type() const {
    return &hitbox_type_;
}

const SDL_Rect* Hitbox::hitbox() const {
    return &hitbox_;
}

const Circle* Hitbox::hitbox_circle() const {
    return &circle_hitbox_;
}
