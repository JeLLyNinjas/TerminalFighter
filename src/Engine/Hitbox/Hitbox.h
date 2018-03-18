#pragma once

#include "I_Hitbox.h"

class Hitbox : public I_Hitbox {
public:
    Hitbox(double x_pos, double y_pos, double width, double height);
    Hitbox(double x_pos, double y_pos, double radius);
    Hitbox(JN_Rect hitbox);
    Hitbox(Circle hitbox);

    bool is_overlapping(const I_Hitbox& other_hitbox) const;
    void set_pos(double x, double y);
    const JN_Rect& hitbox() const;
    const Circle& hitbox_circle() const;
    const Shape::Shape& hitbox_type() const;

protected:
    JN_Rect hitbox_;
    Circle circle_hitbox_;
    Shape::Shape hitbox_type_;

private:
    bool check_overlap(const Circle& hitbox, const Circle& other_hitbox) const;
    bool check_overlap(const Circle& hitbox, const JN_Rect& other_hitbox) const;
    bool check_overlap(const JN_Rect& hitbox, const JN_Rect& other_hitbox) const;
    bool jn_has_intersection(const JN_Rect& hitbox, const JN_Rect& other_hitbox) const;
};
