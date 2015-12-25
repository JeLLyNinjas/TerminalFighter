#include "universe.h"


Universe::Universe(SDL_Renderer *renderer) {
    renderer_ = renderer;
}

void Universe::get_events() {

}

void Universe::update_all() {
    for (Game_Object * game_object : all_game_objects) {
        game_object->update();
    }
}

void Universe::draw_all() {
            
}

/***********
 *listeners 
 ***********/

void Universe::notify_missile_launched(Missile *missile) {
    all_game_objects.push_back(missile);
}


