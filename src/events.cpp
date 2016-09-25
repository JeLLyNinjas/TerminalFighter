#include "events.h"

void Events::notify_event(SDL_Event e) {
    for(EventsListener *listener : listeners) {
        listener->notify_events(e);
    }
}

void Events::update() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
       notify_event(event);
    }
}
