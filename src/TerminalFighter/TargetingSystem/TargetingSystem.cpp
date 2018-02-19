#include <fstream>
#include <cstdlib>
#include <ctime>

#include <glog/logging.h>
#include <SDL_ttf.h>

#include "GraphicsHandler/I_GraphicsHandler.h"
#include "TF_Colors/TF_Colors.h"

#include "TargetingSystem.h"

namespace {
    int FONT_SIZE = 160;
    unsigned int MAX_WORD_LENGTH = 30;
}

TargetingSystem::TargetingSystem(
    int word_length_lower_bound,
    int word_length_upper_bound,
    std::string dict_path,
    std::string font_path,
    std::string color_hex)
    : hitbox_(Hitbox(0, 0, 1920, 1080)) //hardcoded numbers, TODO, don't have these hardcoded
    , word_length_lower_bound_(word_length_lower_bound)
    , word_length_upper_bound_(word_length_upper_bound)
    , color_hex_(color_hex) 
    , font_path_(font_path) {
    setup_local_dict(dict_path);

    srand(time(NULL)); //TODO this should be called at a higher level, maybe Universe //this actually makes rand() be random
}

TargetingSystem::~TargetingSystem() {
}

bool TargetingSystem::setup_local_dict(std::string relative_path) {
    std::ifstream infile(relative_path);

    if (!infile) {
        LOG(ERROR) << "Failed to load dictionary: " << relative_path;
        return false;
    }

    //local_dict_ is 2D vector. 1st dimension is used to split words on length
    //where index represents word length, 2nd dimension holds the words
    local_dict_.resize(MAX_WORD_LENGTH);

    for (std::string line; std::getline(infile, line); ) {
        if (line.length() < MAX_WORD_LENGTH) {
            local_dict_[line.length()].push_back(line);
        }
    }

    infile.close();
    return true;
}

/*if lower_bound is same or greater than upper_bound, than lower_bound will be used and upper_bound will be ignored*/
std::string TargetingSystem::grab_word() {
    int random_word_length;

    if ((word_length_upper_bound_ - word_length_lower_bound_) < 1) {
        random_word_length = word_length_upper_bound_;
    } else {
        random_word_length = word_length_lower_bound_ +
                             (rand() % (word_length_upper_bound_ - word_length_lower_bound_));
    }

    return local_dict_[random_word_length].at(rand() % local_dict_[random_word_length].size());
}

void TargetingSystem::update() {
    //LOG(INFO) << "Checking for heartbeats...";

    std::map<int, GameObjectStringPair*>::iterator it = targets_.begin();

    while (it != targets_.end()) {
        //LOG(INFO) << "checking target id: " << it->first;

        if (it->second->alive_ == true) {
            //LOG(INFO) << "status: alive";
            it->second->alive_ = false;
            it++;
        } else {
            //LOG(INFO) << "status: deleted";
            std::map<int, GameObjectStringPair*>::iterator to_delete = it;
            it++;
            delete (to_delete->second);
            targets_.erase(to_delete);
        }
    }
}

void TargetingSystem::draw(I_GraphicsHandler& graphics) {

    // Byron: Opting not to use `auto` for clarity on the iterator `it`
    for (std::map<int, GameObjectStringPair*>::iterator it = targets_.begin(); it != targets_.end(); ++it) {
        graphics.draw_text(it->second->assigned_word_.c_str(),
                RenderType::Blended,
                font_path_,
                TF_Colors::WHITE,
                40,
                0.05,
                it->second->game_object_.x_pos(),
                it->second->game_object_.y_pos());


    }
}

const I_Hitbox& TargetingSystem::hitbox() const {
    return hitbox_;
}

void TargetingSystem::notify_collision(GameObject& collided_object) {

    if (targets_.find(collided_object.id()) != targets_.end()) {
        targets_.find(collided_object.id())->second->alive_ = true;
    } else {
        targets_[collided_object.id()] =
            new GameObjectStringPair(grab_word(), collided_object, true);
    }

}

void TargetingSystem::take_damage(int damage) {
    //do nothing;
}


void TargetingSystem::print_dict() {
    for (unsigned int i = 0; i < local_dict_.size(); i++) {
        for (unsigned int j = 0; j < local_dict_[i].size(); j++) {
            LOG(INFO) << local_dict_[i].at(j).c_str();
        }
    }
}

GameObject* TargetingSystem::get_object(std::string word) {
    for (std::map<int, GameObjectStringPair*>::iterator it = targets_.begin(); it != targets_.end(); ++it) {
        if (it->second->assigned_word_.compare(word) == 0) {
            return &it->second->game_object_;
        }
    }

    return NULL;
}
