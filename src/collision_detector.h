#pragma once
#include <vector>

#include "I_collision_detector.h"
#include "sensor.h"
#include "projectile.h"
#include "ship.h"
#include "game_object.h"

class CollisionDetector : public I_CollisionDetector {
public:
    CollisionDetector();
    ~CollisionDetector();

    void add_projectile(Team::Team team, Projectile& projectile);
    void add_game_object(Team::Team team, GameObject& game_object);
    void check_friendly_sensor_collisions();
    void check_enemy_sensor_collisions();
    void check_friendly_projectile_collisions();
    void check_enemy_projectile_collisions();
    void check_friendly_ship_collisions();
    void check_enemy_ship_collisions();

private:
    std::vector<Sensor*> friendly_sensors_;
    std::vector<Sensor*> enemy_sensors_;
    std::vector<Projectile*> friendly_projectiles_;
    std::vector<Projectile*> enemy_projectiles_;
    std::vector<Ship*> friendly_ships_;
    std::vector<Ship*> enemy_ships_;
};
