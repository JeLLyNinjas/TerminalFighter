#pragma once

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "Hitbox.h"

class I_Hitbox;

class BasicEnemy : public GameObject {
public:
    BasicEnemy(double x_pos, double y_pos, double x_vel, double y_vel);

    void update();
    void draw(GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

    static void set_texture(SDL_Texture* texture);

protected:
    Hitbox hitbox_;

private:
    static SDL_Texture* texture_;
};
