#include "universe.h"

Universe::Universe(SDL_Renderer *renderer) {
    graphics_handler_ = new GraphicsHandler(renderer);
    graphics_handler_->init();
}

void Universe::get_events() {

}

void Universe::update_all() {
    for (auto& game_object : all_game_objects_) {
        game_object->update();
    }
}

void Universe::draw_all() {
    for (auto& game_object : all_game_objects_) {
        game_object->draw(graphics_handler_);
    }
}

void Universe::draw_to_screen() {
    graphics_handler_->update_screen();
}

void Universe::remove_deleted_objects() {
    //TODO
}

void Universe::add_events_handler(std::unique_ptr<Events> events) {
    all_game_objects_.push_back(std::move(events));
}

void Universe::add_game_object(std::unique_ptr<GameObject> game_object) {
    all_game_objects_.push_back(std::move(game_object));
}

