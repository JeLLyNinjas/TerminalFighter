#pragma once

#include "game_object.h"
#include "hitbox.h"
#include "projectile.h"
#include "ship.h"
#include <vector>

class Sensor : public GameObject {

public:
	Sensor(double x_pos, double y_pos)
		: GameObject(x_pos, y_pos)
	{ }

	virtual void update() = 0;
	virtual void draw(GraphicsHandler* graphics) = 0;
	virtual std::vector<Hitbox> get_hitboxes() = 0;
	virtual void notify_collision(Sensor* sensed_sensor, int hitbox_number);
	virtual void notify_collision(Projectile* sensed_sensor, int hitbox_number);
	virtual void notify_collision(Ship* sensed_sensor, int hitbox_number);
};
