#pragma once

#include <stdio.h>
#include <memory>

#include "GameObject/GameObject.h"
#include "Hitbox/Hitbox.h"

class I_Hitbox;
class I_GraphicsHandler;
class SDL_Texture;

class MainCharacter : public GameObject {
public:
    MainCharacter(double x_pos, double y_pos, int health);
    static void set_texture(SDL_Texture* texture);
    void add_weapon(std::unique_ptr<GameObject> weapon);

    // GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

protected:
    Hitbox hitbox_;

private:
    static SDL_Texture* texture_;
    std::vector<std::unique_ptr<GameObject>> weapons_;
};
