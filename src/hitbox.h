#pragma once 
#include <SDL2/SDL.h>

class Hitbox { 
public: 
	Hitbox(double x_pos, double y_pos, double width, double height); 	
	Hitbox(SDL_Rect hitbox); 
	bool is_overlapping(Hitbox hitbox1, Hitbox hitbox2);

protected:
	SDL_Rect hitbox_; 
};