#include "universe.h"

Universe::Universe(SDL_Renderer *renderer) {
    graphics_handler_ = new GraphicsHandler(renderer);
    graphics_handler_->init();
}

void Universe::get_events() {

}

void Universe::update_all() {
    for (GameObject *game_object : all_game_objects) {
        game_object->update();
    }
}

void Universe::draw_all() {
    for (GameObject *game_object : all_game_objects) {
        game_object->draw(graphics_handler_);
    }
}

void Universe::draw_to_screen() {
    graphics_handler_->update_screen();
}

void remove_deleted_objects() {
    //TODO
}

/* listeners */
void Universe::notify_projectile_launched(Projectile *projectile, Team team) {
    all_game_objects.push_back(projectile);
}