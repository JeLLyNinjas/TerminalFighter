#pragma once

#include <SDL2/SDL.h>

#include "EventsListener.h"
#include "I_Updatable.h"
#include "Observable.h"

class Events : public I_Updatable, public Observable<EventsListener> {

public:
    Events();
    void update();

private:
    void notify_event(SDL_Event e);
};

