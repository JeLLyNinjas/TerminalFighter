#include "TargetingSystem.h"


TargetingSystem::TargetingSystem(int word_length_lb, int word_length_ub, std::string color_hex)
    : word_length_lb_(word_length_lb)
    , word_length_ub_(word_length_ub)
    , color_hex_(color_hex) {
    setup_local_dict("placeholder");
}

void TargetingSystem::setup_local_dict(std::string relative_path) {

    std::ifstream infile("assets/dictionary.txt");

    //local_dict_ is 2D vector. 1st dimension is used to split words on length
    //where index represents word length, 2nd dimension holds the words
    local_dict_.resize(30);

    for (std::string line; std::getline(infile, line); ) {
        if (line.length() < 30) {
            local_dict_[line.length()].push_back(line);
        }
    }

    infile.close();

    std::printf("%s\n", grab_word(1, 7).c_str());
}

/*if lb is same or greater than ub, than lb will be used and ub will be ignored*/
std::string TargetingSystem::grab_word(int lb, int ub) {
    srand(time(NULL)); //this actually makes rand() be random
    int random_word_length;

    if ((ub - lb) < 1) {
        random_word_length = ub;
    } else {
        random_word_length = lb + (rand() % (ub - lb));
    }

    return local_dict_[random_word_length].at(rand() % local_dict_[random_word_length].size());
}

void TargetingSystem::update() {

}

void TargetingSystem::draw(I_GraphicsHandler& graphics) {

}

const I_Hitbox& TargetingSystem::hitbox() const {

}

void TargetingSystem::notify_collision(GameObject& collided_object) {

}


void TargetingSystem::debug_vector() {
    for (int i = 0; i < local_dict_.size(); i++) {
        printf("%s %d\n", "Word of size:", i);

        for (int j = 0; j < local_dict_[i].size(); j++) {
            printf("%s\n", local_dict_[i].at(j).c_str());
        }
    }
}
