#include <stdio.h>

#include <SDL2/SDL.h>

#include "Terminal.h"
#include "GraphicsHandler.h"

SDL_Texture* Terminal::terminal_texture_ = NULL;

Terminal::Terminal(double x_pos, double y_pos, double width, double height)
    : GameObject(x_pos, y_pos, 0.0, 0.0)
    , hitbox_(Hitbox(x_pos, y_pos, width, height)) {
}

void Terminal::draw(I_GraphicsHandler& graphics) {
    if (terminal_texture_ == NULL) {
        printf("Terminal graphics were null! Setting terminal graphic...\n");
        set_texture(graphics.load_image("assets/terminal/futureui1.png"));
    }

    graphics.draw(terminal_texture_, (int)x_pos(), (int)y_pos(), GraphicPriority::UI);
}

const I_Hitbox& Terminal::hitbox() const {
    return hitbox_;
}

void Terminal::update() {
    //do nothing
}
void Terminal::notify_collision(GameObject& collided_object) {
    //do nothing
}
void Terminal::set_texture(SDL_Texture* texture) {
    terminal_texture_ = texture;
}

void Terminal::handle_key_press(const std::string& keypress) {
    printf("Hello!@\n");
}
