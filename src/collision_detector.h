#pragma once
#include <SDL_rect.h>

class Game_Object;

class CollisionDetector : public I_CollisionDetector {
public:
	void update_collisions();

private:
	std::vector<Game_Object*> gameObjects_;
};