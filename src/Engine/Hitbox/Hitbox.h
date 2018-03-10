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
    SDL_Rect hitbox_;
    Circle circle_hitbox_;
    Shape::Shape hitbox_type_;

private:
    bool check_overlap(const Circle& hitbox, const Circle& other_hitbox) const;
    bool check_overlap(const Circle& hitbox, const SDL_Rect& other_hitbox) const;
    bool check_overlap(const SDL_Rect& hitbox, const SDL_Rect& other_hitbox) const;
};
