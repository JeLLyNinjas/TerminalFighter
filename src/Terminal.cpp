#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "Terminal.h"
#include "GraphicsHandler.h"

SDL_Texture* Terminal::terminal_texture_ = NULL;

Terminal::Terminal(double x_pos, double y_pos, double width, double height)
    : GameObject(x_pos, y_pos, 0.0, 0.0, 0)
    , hitbox_(Hitbox(x_pos, y_pos, width, height))
    , player_text_("")
    , default_font_ (TTF_OpenFont("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf", 84)) {
}

void Terminal::draw(I_GraphicsHandler& graphics) {
    if (terminal_texture_ == NULL) {
        printf("Terminal graphics were null! Setting terminal graphic...\n");
        set_texture(graphics.load_image("assets/terminal/futureui1.png"));
    }

    SDL_Color white = {255, 255, 255};
    SDL_Surface* UIText = TTF_RenderText_Blended(default_font_, player_text_.c_str(), white);
    graphics.draw(terminal_texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::UI);
    graphics.draw(UIText, (int)x_pos() + 30, (int)y_pos() + 30, GraphicPriority::UI);
    SDL_FreeSurface(UIText);
}

const I_Hitbox& Terminal::hitbox() const {
    return hitbox_;
}

void Terminal::update() {
    //do nothing - TODO: maybe add cool effects one day
}
void Terminal::notify_collision(GameObject& collided_object) {
    //do nothing
}
void Terminal::set_texture(SDL_Texture* texture) {
    terminal_texture_ = texture;
}

void Terminal::handle_key_press(const std::string& keypress) {
    if (keypress.length() == 1) {
        player_text_ = player_text_ + keypress;
    } else if (keypress.compare("BKSPACE") == 0) {
        if (player_text_.length() != 0) {
            player_text_.resize(player_text_.length() - 1);
        }
    } else if (keypress.compare("ENTER") == 0) {
        notify_input(player_text_);
        player_text_.resize(0);
    }
}

void Terminal::notify_input(const std::string& input) {
    for (TerminalListener* listener : Observable<TerminalListener>::listeners_) {
        listener->handle_input(input);
    }
}
