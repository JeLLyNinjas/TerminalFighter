#pragma once

#include "events_listener.h"
#include "game_object.h" 
#include "graphics_handler.h"
#include "observable.h"
#include <SDL2/SDL.h>

class Events : public GameObject, public Observable<EventsListener> {

public: 
    Events() 
    : GameObject(0, 0) //default coordinates. 
    { }

    /* Events will have an empty draw */
    void draw(GraphicsHandler *graphics) { };
    void update();

private:
    void notify_event(SDL_Event e);

};

