#pragma once

#include "I_GameObjectMediator.h"

class I_Universe;
class I_CollisionDetector;

class GameObjectMediator : public I_GameObjectMediator {

public:
    GameObjectMediator(I_Universe& universe, I_CollisionDetector& collision_detector, I_AudioHandler& audio);
    void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object);
    void add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile);
    void play_sound(std::string path);

private:
    I_Universe& universe_;
    I_CollisionDetector& collision_detector_;
    I_AudioHandler& audio_;
};
