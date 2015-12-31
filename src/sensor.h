#pragma once

#include "game_object.h"

class Sensor : public GameObject {
	Sensor(double x_pos, double y_pos)
	: GameObject(x_pos, y_pos)
	{ }

	virtual void update() = 0;
	virtual void draw(GraphicsHandler* graphics) = 0;
	virtual void get_hitboxes() = 0; 
};
