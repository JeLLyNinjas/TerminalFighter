#pragma once

#include "Engine/GameObject.h"
#include "Engine/Hitbox.h"

class I_Hitbox;
class I_GraphicsHandler;
class SDL_Texture;

class Missile : public GameObject {
public:
    Missile(double x_pos, double y_pos, double x_vel, double y_vel);
    ~Missile();

    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

    static void set_texture(SDL_Texture* texture);

private:
    static SDL_Texture* missile_texture_;
    Hitbox hitbox_;
};
