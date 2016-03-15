#pragma once

#include "game_object.h"
#include "keyboard_listener.h"
#include "observable.h"
#include <SDL2/SDL.h>
#include <string>
#include "graphics_handler.h"


/* Keyboard
 * Will return a single character std::string when a keypress is made
 * Will return non-single character std::string when the following keypresses are made
 *  Button              Return Value
 *  Left arrow          LEFT         
 *  Right arrow         RIGHT
 *  Up arrow            UP
 *  Down arrow          DOWN
 *  Space Key           SPACE
 *  Backspace           BKSPACE
 *  Esc Key             ESC
 *  Enter Key           ENTER
 *  Forward Slash       SLASH
 *  
 */

class Keyboard : public GameObject, public Observable<KeyboardListener> {

public: 
    Keyboard() 
    : GameObject(0, 0) //default coordinates. 
    { }

    /* Keyboard will have an empty draw */
    void draw(GraphicsHandler *graphics) { };
    void update();

private:
    void notify_key(std::string key);

};

