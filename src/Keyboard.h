#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "KeyboardListener.h"
#include "Observable.h"
#include "GraphicsHandler.h"
#include "EventsListener.h"


/* Keyboard
 * Listens to events.h using the "notify_events" function. Keyboard will then look for events that are keyboard related
 * and return characters. 
 * Will return a single character std::string when a keypress is made
 * Will return non-single character std::string when the following keypresses are made
 *  [Button]            [Return Value]
 *  Left arrow          LEFT         
 *  Right arrow         RIGHT
 *  Up arrow            UP
 *  Down arrow          DOWN
 *  Backspace           BKSPACE
 *  Esc Key             ESC
 *  
 */

class Keyboard : public EventsListener, public Observable<KeyboardListener> {

public: 
    Keyboard() { };

    /* Keyboard will have an empty draw */
private:

    void notify_events(SDL_Event e);
    void notify_key(std::string key);

};

