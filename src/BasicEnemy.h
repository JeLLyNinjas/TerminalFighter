#pragma once

#include "GameObject.h"
#include "Hitbox.h"

class SDL_Texture;
class I_Hitbox;
class I_GraphicsHandler;

class BasicEnemy : public GameObject {
public:
    BasicEnemy(double x_pos, double y_pos, double x_vel, double y_vel, int health);

    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);
    void take_damage(int damage);

    static void set_texture(SDL_Texture* texture);

protected:
    Hitbox hitbox_;

private:
    static SDL_Texture* texture_;
};
