#pragma once

#include "GameObject.h"
#include "Hitbox.h"
#include "KeyboardListener.h"
#include "Keyboard.h"
#include "Observable.h"
#include "TerminalListener.h"

#include <SDL_ttf.h>
#include <string>

class Terminal : public GameObject, public Observable<TerminalListener> {
public:
    //x_pos and y_pos define top left portion of terminal
    Terminal(double x_pos, double y_pos, double width, double height);
    void handle_key_press(const std::string& keypress);

    //GameObject
    void update();
    void draw(I_GraphicsHandler& graphics);
    const I_Hitbox& hitbox() const;
    void notify_collision(GameObject& collided_object);

private:
    void notify_input(const std::string& input);
    static void set_texture(SDL_Texture* texture);

    static SDL_Texture* terminal_texture_;
    std::string player_text_;
    TTF_Font* default_font_;
    Hitbox hitbox_;
};
