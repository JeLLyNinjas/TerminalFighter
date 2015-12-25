#pragma once
#include <vector>

#include "game_object.h"
#include "missile_launcher_listener.h"
#include "graphics_handler.h"

class Universe : public MissileLauncherListener {

public:
    Universe(SDL_Renderer *renderer);
    void get_events();
    void update_all();
    void draw_all();
    void draw_to_screen();


    /***********
     *listeners 
     ***********/
    void notify_missile_launched(Missile *missile);

private:
    void remove_deleted_objects();  /*removes all empty/NULL objects from the all_game_objects vector*/

    std::vector<Game_Object*> all_game_objects;
    GraphicsHandler *graphics_handler_;
};
