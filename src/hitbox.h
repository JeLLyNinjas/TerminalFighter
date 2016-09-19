#pragma once
#include <SDL2/SDL.h>

struct Circle
{
    int x, y;
    int r;
};

enum Shape {rect, circle};

class Hitbox {
    public:
        Hitbox(double x_pos, double y_pos, double width, double height);
        Hitbox(double x_pos, double y_pos, double radius);
        Hitbox(SDL_Rect hitbox);
        Hitbox(Circle hitbox);

        bool is_overlapping(const Hitbox& other_hitbox);
        const SDL_Rect* hitbox() const;
        const Circle* hitbox_circle() const;
        const Shape* hitbox_type() const;

    protected:
        SDL_Rect hitbox_;
        Circle circle_hitbox_;
        Shape hitbox_type_;

    private:
        bool check_overlap(const Circle &hitbox, const Circle& other_hitbox);
        bool check_overlap(const Circle &hitbox, const SDL_Rect &other_hitbox);
        bool check_overlap(const SDL_Rect &hitbox, const SDL_Rect &other_hitbox);
};
