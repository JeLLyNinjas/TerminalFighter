#pragma once

#include <memory>
#include <string>

#include "Team/Team.h"
#include "GameObject/GameObject.h"

/**
 * A GameObjectMediator provides an interface for GameObjects to interact with
 * large components of the engine, without needing to have full access to them.
 */
class I_GameObjectMediator {
public:
    virtual ~I_GameObjectMediator() {}
    /**
     * This function allows gameobjects to add new gameobjects to the game space.
     * The new object must be instantiated as a unique_ptr and upon calling this function,
     * the creator will lose ownership.
     * After calling this function, the new game_object will be updated independently by the universe.
     * The creator should not update the object after calling this function. 
     * @param team indicates what team the new object belongs on, objects on the same team do not collide
     * @param game_object is a unique_ptr to the new game_object, the caller loses ownership after calling this func
     */
    virtual void add_game_object(Team::Team team, std::unique_ptr<GameObject> game_object) = 0;

    /**
     * This function is similar to <code>add_game_object()</code> except it's to add projectiles.
     * The difference is that projectiles won't collide with other projectiles.
     * Refer to <code>add_game_object()</code> for more information.
     */
    virtual void add_projectile(Team::Team team, std::unique_ptr<GameObject> projectile) = 0;

    /**
     * This function gives access to play sounds in the sound engine.
     * @param the relative path to the sound to be played.
     */
    virtual void play_sound(std::string path) const = 0;
};
