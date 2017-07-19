#include "TargetingSystem.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

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
std::string TargetingSystem::grab_word(int lower_bound, int upper_bound) {
    srand(time(NULL)); //this actually makes rand() be random
    int random_word_length;

    if ((upper_bound - lower_bound) < 1) {
        random_word_length = upper_bound;
    } else {
        random_word_length = lower_bound + (rand() % (upper_bound - lower_bound));
    }

    return local_dict_[random_word_length].at(rand() % local_dict_[random_word_length].size());
}

void TargetingSystem::update() {
    //no update
}

void TargetingSystem::draw(I_GraphicsHandler& graphics) {
    //no draw
}

const I_Hitbox& TargetingSystem::hitbox() const {
    return hitbox_;
}

void TargetingSystem::notify_collision(GameObject& collided_object) {
    //printf("Collision with objectID:%d\n", collided_object.id());
    if (targets_.find(&collided_object) != targets_.end()) {

    } else {
        printf("Target %d was not found\n", collided_object.id());
        targets_[&collided_object] = {grab_word(word_length_lower_bound_, word_length_upper_bound_), "1"};
    }
}


void TargetingSystem::print_dict() {
    for (int i = 0; i < local_dict_.size(); i++) {
        for (int j = 0; j < local_dict_[i].size(); j++) {
            printf("%s\n", local_dict_[i].at(j).c_str());
        }
    }
}
