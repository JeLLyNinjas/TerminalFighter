#pragma once

#include "I_Hitbox.h"

class Hitbox : public I_Hitbox {
public:
    Hitbox(int x_pos, int y_pos, int width, int height);
    Hitbox(int x_pos, int y_pos, int radius);
    Hitbox(SDL_Rect hitbox);
    Hitbox(Circle hitbox);

    bool is_overlapping(const I_Hitbox& other_hitbox) const;
    void set_pos(int x, int y);
    const SDL_Rect& hitbox() const;
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
