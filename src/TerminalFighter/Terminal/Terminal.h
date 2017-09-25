#pragma once

#include <SDL_ttf.h>
#include <string>

#include "GameObject/GameObject.h"
#include "Hitbox/Hitbox.h"
#include "Keyboard/KeyboardListener.h"
#include "Keyboard/Keyboard.h"
#include "Observable/Observable.h"

#include "TerminalListener.h"


class Terminal : public GameObject, public Observable<TerminalListener> {
public:
    //x_pos and y_pos define top left portion of terminal
    Terminal(double x_pos, double y_pos, double width, double height);
    ~Terminal();
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
    Hitbox hitbox_;
    std::string player_text_;
    TTF_Font* default_font_;
};
