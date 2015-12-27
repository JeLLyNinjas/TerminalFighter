#pragma once 
#include <SDL_rect.h>

class Game_Object; 

class Collidable {
public:
	virtual void collided(const std::vector< std::vector<Game_Object*> > collisions) = 0;
	std::vector<SDL_Rect> hitboxes() { return hitboxes; };

protected:
	std::vector<SDL_Rect> hitboxes_;
};