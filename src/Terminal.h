#pragma once

#include "GameObject.h"
#include "Hitbox.h"
#include "KeyboardListener.h"
#include "Keyboard.h"

class Terminal : public GameObject, public KeyboardListener {
public:
    //x_pos and y_pos define top left portion of terminal
    Terminal(double x_pos, double y_pos, double width, double height);

    //GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

    //KeyboardListener
    void handle_key_press(const std::string& keypress);

    static void set_texture(SDL_Texture* texture);
private:
    static SDL_Texture* terminal_texture_;
    Hitbox hitbox_;
};
