#pragma once

#include "GameObject.h"
#include "Hitbox.h"

class I_Hitbox;
class I_GraphicsHandler;
class SDL_Texture;

class MainCharacter : public GameObject {
public:
    MainCharacter(double x_pos, double y_pos);

    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

    static void set_texture(SDL_Texture* texture);

protected:
    Hitbox hitbox_;

private:
    static SDL_Texture* texture_;
};
