#include "hitbox.h"


Hitbox::Hitbox(double x_pos, double y_pos, double width, double height){
	hitbox_.x = x_pos;
	hitbox_.y = y_pos;
	hitbox_.w = width; 
	hitbox_.h = height; 
}	

Hitbox::Hitbox(SDL_Rect hitbox) {
	hitbox_ = hitbox; 
}

bool Hitbox::is_overlapping(Hitbox hitbox1, Hitbox hitbox2){
	return SDL_HasIntersection(&hitbox1.hitbox_, &hitbox2.hitbox_); 
}
