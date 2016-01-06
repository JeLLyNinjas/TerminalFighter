#pragma once 
#include <SDL2/SDL.h>

class Hitbox { 
public: 
	Hitbox(double x_pos, double y_pos, double width, double height); 	
	Hitbox(SDL_Rect hitbox); 
	bool is_overlapping(const Hitbox& other_hitbox);
	const SDL_Rect& hitbox() const;

protected:
	SDL_Rect hitbox_; 
};