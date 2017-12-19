#pragma once

#include "I_Hitbox.h"

class Hitbox : public I_Hitbox {
public:
    Hitbox(double x_pos, double y_pos, double width, double height);
    Hitbox(double x_pos, double y_pos, double radius);
    Hitbox(Rect hitbox);
    Hitbox(Circle hitbox);

    bool is_overlapping(const I_Hitbox& other_hitbox) const;
    void set_pos(double x, double y);
    const Rect& hitbox() const;
    const Circle& hitbox_circle() const;
    const Shape::Shape& hitbox_type() const;

private:
    Rect hitbox_;
    Circle circle_hitbox_;
    Shape::Shape hitbox_type_;

    bool check_overlap(const Circle& hitbox, const Circle& other_hitbox) const;
    bool check_overlap(const Circle& hitbox, const Rect& other_hitbox) const;
    bool check_overlap(const Rect& hitbox, const Rect& other_hitbox) const;
};
