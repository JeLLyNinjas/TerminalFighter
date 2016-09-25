#pragma once

#include <SDL2/SDL.h>

#include "events_listener.h"
#include "I_Updatable.h"
#include "observable.h"

class Events : public I_Updatable, public Observable<EventsListener> {

public:
    Events() {}

    void update();

private:
    void notify_event(SDL_Event e);
};

