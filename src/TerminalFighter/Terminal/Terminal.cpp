#include <glog/logging.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "TF_Colors/TF_Colors.h"
#include "GraphicsHandler/I_GraphicsHandler.h"

#include "Terminal.h"

SDL_Texture* Terminal::terminal_texture_ = NULL;

Terminal::Terminal(
    double x_pos, double y_pos,
    double width, double height,
    std::string graphic_path,
    std::string font_path)
    : GameObject(x_pos, y_pos, width, height, 0.0, 0.0, 0)
    , hitbox_(Hitbox(x_pos, y_pos, width, height))
    , terminal_texture_path_(graphic_path)
    , player_text_("")
    , font_path_ (font_path) {
}

Terminal::~Terminal() {
}

void Terminal::draw(I_GraphicsHandler& graphics) {
    if (terminal_texture_ == NULL) {
        LOG(WARNING) << "Terminal graphics were null! Setting terminal graphic...";
        set_texture(graphics.load_image(terminal_texture_path_));
    }

    int terminal_w, terminal_h;
    SDL_QueryTexture(terminal_texture_, NULL, NULL, &terminal_w, &terminal_h);

    graphics.draw(terminal_texture_,
                  graphics.create_sdl_rect(0, 0, terminal_w, terminal_h),
                  graphics.create_jn_rect(x_pos(), y_pos(), width(), height()),
                  GraphicPriority::UI,
                  false,
                  0,
                  NULL);

    std::string output_string;
    // To prevent RenderText from complaining about an empty string
    if (player_text_.length() == 0) {
        output_string = " ";
    } else {
        output_string = player_text_;
    }
    graphics.draw_text(output_string.c_str(),
            RenderType::Blended,
            font_path_,
            TF_Colors::WHITE,
            70,
            0.22,
            x_pos() + 0.05,
            y_pos());
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
