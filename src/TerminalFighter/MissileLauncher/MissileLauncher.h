#pragma once

#include <string>
#include <stdlib.h>

#include "Team/Team.h"
#include "GameObjectMediator/I_GameObjectMediator.h"

#include "Terminal/Terminal.h"
#include "TargetingSystem/TargetingSystem.h"
#include "Terminal/TerminalListener.h"

class I_GameObjectMediator;

class MissileLauncher : public GameObject, public KeyboardListener, public TerminalListener {
public:
    MissileLauncher(
        Team::Team team,
        I_GameObjectMediator& game_object_mediator,
        std::string missile_graphic_path,
        std::string terminal_graphic_path,
        std::string terminal_font_path,
        std::string targeting_system_font_path,
        std::string targeting_system_dict_path,
        std::string missile_sound_path,
        double x_pos, double y_pos);
    Team::Team team() const;
    void create_missile(double x_vel, double y_vel, double x_pos, double y_pos);
    void handle_key_press(const std::string& keypress);

    // GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);
    void handle_input(const std::string& input);
    //virtual void object_destroyed(int id);

private:
    Team::Team team_;
    I_GameObjectMediator& game_object_mediator_;
    std::string missile_graphic_path_;
    std::string missile_launch_sound_path_;
    Terminal terminal_;
    TargetingSystem* targeting_system_;
    Hitbox hitbox_;
};
