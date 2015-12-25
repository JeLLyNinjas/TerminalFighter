#include "universe.h"

Universe::Universe(SDL_Renderer *renderer) {
    graphics_handler_ = new GraphicsHandler(renderer);
}

void Universe::get_events() {

}

void Universe::update_all() {
    for (Game_Object *game_object : all_game_objects) {
        game_object->update();
    }
}

void Universe::draw_all() {
    for (Game_Object *game_object : all_game_objects) {
        printf("Calling draw_all\n");
        game_object->draw(graphics_handler_);
    }
}

void Universe::draw_to_screen() { 
    graphics_handler_->update_screen(); 
}

void remove_deleted_objects() {
    //TODO
}

/***********
 *listeners 
 ***********/

void Universe::notify_missile_launched(Missile *missile) {
    printf("got a missile notification!\n");
    all_game_objects.push_back(missile);
}



