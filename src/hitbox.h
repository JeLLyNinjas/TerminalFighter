#pragma once 
#include <SDL2/SDL.h>

struct Circle
{
    int x, y;
    int r;
};

class Hitbox { 
public: 
	Hitbox(double x_pos, double y_pos, double width, double height); 	
    Hitbox(double x_pos, double y_pos, double radius);
	Hitbox(SDL_Rect hitbox); 
    Hitbox(Circle hitbox);
    
	bool is_overlapping(Hitbox& other_hitbox);
	const SDL_Rect& hitbox() const;
    const Circle& hitbox_circle() const;

protected:
    SDL_Rect hitbox_; 
    Circle circle_hitbox_;

private:
    bool check_collision(Circle &hitbox, Circle& other_hitbox);
    bool check_collision(Circle &hitbox, SDL_Rect &other_hitbox);
    bool check_collision(SDL_Rect &hitbox, SDL_Rect &other_hitbox);
};
