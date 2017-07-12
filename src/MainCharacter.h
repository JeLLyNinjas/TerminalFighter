#pragma once

#include "GameObject.h"
#include "Hitbox.h"
#include "MissileLauncher.h"

class I_Hitbox;
class I_GraphicsHandler;
class SDL_Texture;

class MainCharacter : public GameObject, public KeyboardListener {
public:
    MainCharacter(double x_pos, double y_pos, I_GameObjectMediator& game_object_mediator);
    static void set_texture(SDL_Texture* texture);

    // GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

    // KeyboardListener
    void handle_key_press(const std::string& keypress);

protected:
    Hitbox hitbox_;

private:
    static SDL_Texture* texture_;
    MissileLauncher launcher_;
};
