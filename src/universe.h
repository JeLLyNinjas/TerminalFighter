#pragma once

#include <vector>

#include "I_universe.h"

class GraphicsHandler;

class Universe : public I_Universe {

public:
    Universe(SDL_Renderer *renderer);
    void get_events();
    void update_all();
    void draw_all();
    void draw_to_screen();
    void add_game_service(std::unique_ptr<I_Updatable> game_service);
    void add_game_object(std::unique_ptr<GameObject> game_object);

private:
    void remove_deleted_objects();  /*TODO removes all empty/NULL objects from the all_game_objects vector*/

    std::vector<std::unique_ptr<GameObject> > all_game_objects_;
    std::vector<std::unique_ptr<I_Updatable> > game_services_;
    GraphicsHandler *graphics_handler_;
};
