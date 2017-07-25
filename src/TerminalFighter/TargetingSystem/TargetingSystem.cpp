#include <fstream>
#include <cstdlib>
#include <ctime>

#include "TargetingSystem.h"

TargetingSystem::TargetingSystem(int word_length_lower_bound, int word_length_upper_bound, std::string color_hex)
    : word_length_lower_bound_(word_length_lower_bound)
    , word_length_upper_bound_(word_length_upper_bound)
    , hitbox_(Hitbox(0, 0, 1920, 1080)) //hardcoded numbers, TODO, don't have these hardcoded
    , color_hex_(color_hex) {
    setup_local_dict("assets/dictionary.txt");
}

void TargetingSystem::setup_local_dict(std::string relative_path) {

    std::ifstream infile(relative_path);

    //local_dict_ is 2D vector. 1st dimension is used to split words on length
    //where index represents word length, 2nd dimension holds the words
    local_dict_.resize(30);

    for (std::string line; std::getline(infile, line); ) {
        if (line.length() < 30) {
            local_dict_[line.length()].push_back(line);
        }
    }

    infile.close();
}

/*if lower_bound is same or greater than upper_bound, than lower_bound will be used and upper_bound will be ignored*/
std::string TargetingSystem::grab_word() {
    srand(time(NULL)); //this actually makes rand() be random
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
    /*
    for (std::map<int, GameObjectStringPair*>::iterator it = targets_.begin(); it != targets_.end(); ++it) {
        it->second->alive_ = false;
    }
    */

}

void TargetingSystem::draw(I_GraphicsHandler& graphics) {
    //no draw
}

const I_Hitbox& TargetingSystem::hitbox() const {
    return hitbox_;
}

void TargetingSystem::notify_collision(GameObject& collided_object) {
    //printf("Collision with objectID:%d\n", collided_object.id());
    if (targets_.find(collided_object.id()) != targets_.end()) {
        targets_.find(collided_object.id())->second->alive_ = true;
    } else {
        printf("Target %d was not found\n", collided_object.id());
        targets_[collided_object.id()] =
            new GameObjectStringPair(grab_word(), &collided_object, true);
    }

}


void TargetingSystem::print_dict() {
    for (int i = 0; i < local_dict_.size(); i++) {
        for (int j = 0; j < local_dict_[i].size(); j++) {
            printf("%s\n", local_dict_[i].at(j).c_str());
        }
    }
}
