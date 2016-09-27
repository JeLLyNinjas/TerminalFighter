#include "Universe.h"

#include "GraphicsHandler.h"

Universe::Universe(SDL_Renderer& renderer)
    : graphics_handler_(renderer) {
    graphics_handler_.init();
}

void Universe::get_events() {
}

void Universe::update_all() {
    for (auto& game_service : game_services_) {
        game_service->update();
    }

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
    graphics_handler_.update_screen();
}

void Universe::object_destroyed(int id) {
    for (int i = 0; i < all_game_objects_.size(); i++) {
        if (all_game_objects_[i]->id() == id) {
            all_game_objects_.erase(all_game_objects_.begin() + i);
            return;
        }
    }

    SDL_assert(true && "Object to be deleted not found in Universe object vector"); // object to be destroyed not found
}

void Universe::add_game_service(std::unique_ptr<I_Updatable> game_service) {
    game_services_.push_back(std::move(game_service));
}

void Universe::add_game_object(std::unique_ptr<GameObject> game_object) {
    all_game_objects_.push_back(std::move(game_object));
}

void Universe::remove_deleted_objects() {
    //TODO
}
