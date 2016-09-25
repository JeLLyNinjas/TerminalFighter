#include "collision_detector.h"
#include "hitbox.h"

CollisionDetector::CollisionDetector()
{

}


CollisionDetector::~CollisionDetector()
{

}

void CollisionDetector::check_friendly_sensor_collisions() {
    //check friendly_sensors_ against enemy_sensors_, enemy_projectiles_, enemy_ships_
    for (auto friendly_sensor : friendly_sensors_) {
        std::vector<Hitbox> friendly_sensor_hitboxes = friendly_sensor->get_hitboxes();
        for (auto friendly_hitbox : friendly_sensor_hitboxes) {
            int hitbox_number = 0;
            for (auto enemy_sensor : enemy_sensors_) {
                for (auto enemy_hitbox : enemy_sensor->get_hitboxes()) {
                    if (friendly_hitbox.is_overlapping(enemy_hitbox)) {
                        friendly_sensor->notify_collision(enemy_sensor, hitbox_number);
                    }
                }
            }
            for (auto enemy_projectile : enemy_projectiles_) {
                for (auto enemy_hitbox : enemy_projectile->get_hitboxes()) {
                    if (friendly_hitbox.is_overlapping(enemy_hitbox)) {
                        friendly_sensor->notify_collision(enemy_projectile, hitbox_number);
                    }
                }
            }
            for (auto enemy_ship : enemy_ships_) {
                for (auto enemy_hitbox : enemy_ship->get_hitboxes()) {
                    if (friendly_hitbox.is_overlapping(enemy_hitbox)) {
                        friendly_sensor->notify_collision(enemy_ship, hitbox_number);
                    }
                }
            }
            hitbox_number++;
        }
    }
}

void CollisionDetector::check_enemy_sensor_collisions() {
    //check enemy_sensors_ against friendly_sensors_, friendly_projectiles_, friendly_ships_
}

void CollisionDetector::check_friendly_projectile_collisions() {
    //check friendly_projectiles_ against enemy_projectiles_, enemy_ships_
}

void CollisionDetector::check_enemy_projectile_collisions() {
    //check enemy_projectiles_ against friendly_projectiles_, friendly_ships_
}

void CollisionDetector::check_friendly_ship_collisions() {
    //check friendly_ships_ against enemy_ships_
}

void CollisionDetector::check_enemy_ship_collisions() {
    //check enemy_ships_ against friendlysu_ships_
}

void CollisionDetector::add_projectile(Team::Team team, Projectile& projectile)
{

}

void CollisionDetector::add_game_object(Team::Team team, GameObject& game_object)
{

}
