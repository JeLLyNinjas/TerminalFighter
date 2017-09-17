#include "Universe.h"

#include "GraphicsHandler/GraphicsHandler.h"

Universe::Universe(I_GraphicsHandler& graphics_handler, I_AudioHandler& audio_handler)
    : graphics_handler_(graphics_handler)
    , audio_handler_(audio_handler) {
}

void Universe::get_events() {
}

void Universe::update_all() {
    for (auto& game_service : game_services_) {
        game_service->update();
    }

    for (auto& game_object : all_game_objects_) {
        game_object.second->update();
        audio_handler_.play_chunk(audio_handler_.load_chunk(game_object.second->get_sound()));
    }

    for (auto id : id_to_delete_) {
        int success = all_game_objects_.erase(id); // erase returns number of objects erased
        SDL_assert(success && "Object to be deleted not found in Universe object vector"); // object to be destroyed not found
    }

    id_to_delete_.clear();
}

void Universe::draw_all() {
    for (auto& game_object : all_game_objects_) {
        game_object.second->draw(graphics_handler_);
    }
}

void Universe::draw_to_screen() {
    graphics_handler_.update_screen();
}

void Universe::object_destroyed(int id) {
    id_to_delete_.insert(id);
}

void Universe::add_game_service(std::unique_ptr<I_Updatable> game_service) {
    game_services_.push_back(std::move(game_service));
}

void Universe::add_game_object(std::unique_ptr<GameObject> game_object) {
    all_game_objects_[game_object->id()] = std::move(game_object);
}

void Universe::remove_deleted_objects() {
    //TODO
}
