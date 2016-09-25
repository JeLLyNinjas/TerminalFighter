#pragma once
#include <SDL2/SDL.h>

#include "game_object.h"
#include "hitbox.h"

class Missile : public GameObject {
public:
    Missile(double x_pos, double y_pos, double x_vel, double y_vel);

    void update();
    void draw(GraphicsHandler *graphics);
    const Hitbox& hitbox() const;
    void notify_collision(GameObject* collided_object);

    static void set_texture(SDL_Texture* texture);

private:
    static SDL_Texture* missile_texture_;
    Hitbox hitbox_;
};
