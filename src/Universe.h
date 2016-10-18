#pragma once

#include <set>
#include <vector>
#include <map>

#include "I_Universe.h"

class I_GraphicsHandler;

class Universe : public I_Universe {

public:
    Universe(I_GraphicsHandler& graphics_handler);
    void get_events();
    void update_all();
    void draw_all();
    void draw_to_screen();
    void add_game_service(std::unique_ptr<I_Updatable> game_service);
    void add_game_object(std::unique_ptr<GameObject> game_object);
    void object_destroyed(int id);

private:
    void remove_deleted_objects();  /*TODO removes all empty/NULL objects from the all_game_objects vector*/

    std::map<int, std::unique_ptr<GameObject>> all_game_objects_;
    std::set<int> id_to_delete_;
    std::vector<std::unique_ptr<I_Updatable>> game_services_;
    I_GraphicsHandler& graphics_handler_;
};
