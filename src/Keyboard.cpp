#include "Keyboard.h"

void Keyboard::notify_key(std::string key) {
    for(KeyboardListener *listener : listeners) {
        listener->handle_key_press(key);
    }
}

void Keyboard::notify_events(SDL_Event e) {
    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            notify_key("ESC");
            break;
        case SDLK_LEFT:
            notify_key("LEFT");
            break;
        case SDLK_RIGHT:
            notify_key("RIGHT");
            break;
        case SDLK_UP:
            notify_key("UP");
            break;
        case SDLK_DOWN:
            notify_key("DOWN");
            break;
        case SDLK_SPACE:
            notify_key(" ");
            break;
        case SDLK_BACKSPACE:
            notify_key("BKSPACE");
            break;
        case SDLK_SLASH:
            notify_key("/");
            break;
        case SDLK_RETURN:
            notify_key("\n");
            break;
        case SDLK_0:
            notify_key("0");
            break;
        case SDLK_1:
            notify_key("1");
            break;
        case SDLK_2:
            notify_key("2");
            break;
        case SDLK_3:
            notify_key("3");
            break;
        case SDLK_4:
            notify_key("4");
            break;
        case SDLK_5:
            notify_key("5");
            break;
        case SDLK_6:
            notify_key("6");
            break;
        case SDLK_7:
            notify_key("7");
            break;
        case SDLK_8:
            notify_key("8");
            break;
        case SDLK_9:
            notify_key("9");
            break;
        case SDLK_a:
            notify_key("a");
            break;
        case SDLK_b:
            notify_key("b");
            break;
        case SDLK_c:
            notify_key("c");
            break;
        case SDLK_d:
            notify_key("d");
            break;
        case SDLK_e:
            notify_key("e");
            break;
        case SDLK_f:
            notify_key("f");
            break;
        case SDLK_g:
            notify_key("g");
            break;
        case SDLK_h:
            notify_key("h");
            break;
        case SDLK_i:
            notify_key("i");
            break;
        case SDLK_j:
            notify_key("j");
            break;
        case SDLK_k:
            notify_key("k");
            break;
        case SDLK_l:
            notify_key("l");
            break;
        case SDLK_m:
            notify_key("m");
            break;
        case SDLK_n:
            notify_key("n");
            break;
        case SDLK_o:
            notify_key("o");
            break;
        case SDLK_p:
            notify_key("p");
            break;
        case SDLK_q:
            notify_key("q");
            break;
        case SDLK_r:
            notify_key("r");
            break;
        case SDLK_s:
            notify_key("s");
            break;
        case SDLK_t:
            notify_key("t");
            break;
        case SDLK_u:
            notify_key("u");
            break;
        case SDLK_v:
            notify_key("v");
            break;
        case SDLK_w:
            notify_key("w");
            break;
        case SDLK_x:
            notify_key("x");
            break;
        case SDLK_y:
            notify_key("y");
            break;
        case SDLK_z:
            notify_key("z");
            break;
        }
        break;
    }
}




