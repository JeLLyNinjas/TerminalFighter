#pragma once

#include <string>
#include <stdlib.h>

#include "Team/Team.h"
#include "GameObjectMediator/I_GameObjectMediator.h"

#include "GameConstants/GameConstants.h"
#include "Terminal/Terminal.h"
#include "TargetingSystem/TargetingSystem.h"

class I_GameObjectMediator;

class MissileLauncher : public GameObject, public KeyboardListener {
public:
    MissileLauncher(Team::Team team, I_GameObjectMediator& game_object_mediator);
    Team::Team team() const;
    void create_missile(double x_vel, double y_vel, double x_pos, double y_pos);
    void handle_key_press(const std::string& keypress);

    // GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

private:
    Team::Team team_;
    I_GameObjectMediator& game_object_mediator_;
    Terminal terminal_;
    std::unique_ptr<TargetingSystem> targeting_system_;
    Hitbox hitbox_;
};
