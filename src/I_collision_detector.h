#pragma once

#include "game_constants.h"

class Projectile;
class GameObject;

class I_CollisionDetector {
public:
	virtual void add_projectile(Team::Team team, Projectile& projectile) = 0;
	virtual void add_game_object(Team::Team team, GameObject& game_object) = 0;
    virtual void check_friendly_sensor_collisions() = 0;
    virtual void check_enemy_sensor_collisions() = 0;
    virtual void check_friendly_projectile_collisions() = 0;
    virtual void check_enemy_projectile_collisions() = 0;
    virtual void check_friendly_ship_collisions() = 0;
    virtual void check_enemy_ship_collisions() = 0;
};
