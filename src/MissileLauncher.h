#pragma once
#include <string>

#include "GameConstants.h"
#include "I_GameObjectMediator.h"
#include "Terminal.h"
#include "Hitbox.h"

class I_GameObjectMediator;

class MissileLauncher : public GameObject {
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
    Hitbox hitbox_;
};
