#include "Events.h"

Events::Events() {
}

void Events::update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        notify_event(event);
    }
}

void Events::notify_event(SDL_Event e) {
    for (EventsListener* listener : listeners_) {
        listener->notify_events(e);
    }
}
