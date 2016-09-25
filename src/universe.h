#pragma once

#include <vector>

#include "I_universe.h"
#include "game_constants.h"
#include "game_object.h"
#include "graphics_handler.h"
#include "projectile_creator_listener.h"
#include "projectile.h"

class Universe : public I_Universe {

public:
    Universe(SDL_Renderer *renderer);
    void get_events();
    void update_all();
    void draw_all();
    void draw_to_screen();
    void add_events_handler(std::unique_ptr<Events> event);
    void add_game_object(std::unique_ptr<GameObject> game_object);

private:
    void remove_deleted_objects();  /*TODO removes all empty/NULL objects from the all_game_objects vector*/

    std::vector<std::unique_ptr<GameObject> > all_game_objects_;
    GraphicsHandler *graphics_handler_;
};
