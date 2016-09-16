#pragma once

#include <vector>

#include "game_constants.h"
#include "game_object.h"
#include "graphics_handler.h"
#include "projectile_creator_listener.h"
#include "projectile.h"
#include "events.h"

class Universe : public ProjectileCreatorListener {

public:
    Universe(SDL_Renderer *renderer);
    void get_events();
    void update_all();
    void draw_all();
    void draw_to_screen();
    void add_events_handler(Events *event);

    /* listeners */
    void notify_projectile_launched(Projectile *projectile, Team team);

private:
    void remove_deleted_objects();  /*TODO removes all empty/NULL objects from the all_game_objects vector*/

    std::vector<GameObject*> all_game_objects;
    GraphicsHandler *graphics_handler_;
};
