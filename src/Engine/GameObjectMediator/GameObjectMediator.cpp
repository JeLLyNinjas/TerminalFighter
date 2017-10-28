#include <glog/logging.h>

#include "GameObjectMediator.h"

#include "CollisionDetector/I_CollisionDetector.h"
#include "Universe/I_Universe.h"
#include "AudioHandler/AudioHandler.h"

GameObjectMediator::GameObjectMediator(
    I_Universe& universe,
    I_CollisionDetector& collision_detector,
    I_AudioHandler& audio)
    : universe_(universe)
    , collision_detector_(collision_detector)
    , audio_(audio) {
}

void GameObjectMediator::add_game_object(
    Team::Team team,
    std::unique_ptr<GameObject> game_object) {
    collision_detector_.add_game_object(team, *game_object);
    game_object->add_listener(&universe_);
    game_object->add_listener(&collision_detector_);
    universe_.add_game_object(std::move(game_object));
}

void GameObjectMediator::add_projectile(
    Team::Team team,
    std::unique_ptr<GameObject> projectile) {
    projectile->add_listener(&universe_);
    projectile->add_listener(&collision_detector_);
    collision_detector_.add_projectile(team, *projectile);
    universe_.add_game_object(std::move(projectile));
}

void GameObjectMediator::play_sound(std::string path) const {
    Mix_Chunk* sound = audio_.load_chunk(path);

    if (sound == NULL) {
        LOG(ERROR) << "Could not play chunk " << path;
    }

    DLOG(INFO) << "Playing Sound " << path;
    audio_.play_chunk(sound);
}
