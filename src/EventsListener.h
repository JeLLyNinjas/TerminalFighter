#pragma once

#include <SDL2/SDL.h>

class EventsListener {
public:
    virtual void notify_events(SDL_Event e) = 0;
};
