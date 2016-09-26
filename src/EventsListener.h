#pragma once

#include <SDL2/SDL.h>

class EventsListener {
public:
    virtual ~I_EventsListener() {}
    virtual void notify_events(const SDL_Event& e) = 0;
};
