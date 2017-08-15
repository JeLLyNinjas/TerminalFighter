#include <fstream>
#include <cstdlib>
#include <ctime>

#include <SDL_ttf.h>

#include "TargetingSystem.h"
#include "GraphicsHandler/I_GraphicsHandler.h"
#include "GameConstants/GameConstants.h"

TargetingSystem::TargetingSystem(int word_length_lower_bound, int word_length_upper_bound, std::string color_hex)
    : word_length_lower_bound_(word_length_lower_bound)
    , word_length_upper_bound_(word_length_upper_bound)
    , hitbox_(Hitbox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
    , color_hex_(color_hex) {
    setup_local_dict("assets/dictionary.txt");
    srand(time(NULL)); //TODO this should be called at a higher level, maybe Universe //this actually makes rand() be random
    default_font_ = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf", 24);
    white_ = {255, 255, 255};
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
    printf("Checking for heartbeats...\n");

    int x;
    std::map<int, GameObjectStringPair*>::iterator it = targets_.begin();

    while (it != targets_.end()) {
        printf("checking target id: %d...", it->first);

        if (it->second->alive_ == true) {
            printf("status: alive\n");
            it->second->alive_ = false;
            it++;
        } else {
            printf("status: deleted\n");
            std::map<int, GameObjectStringPair*>::iterator to_delete = it;
            it++;
            targets_.erase(to_delete);
        }
    }
}

void TargetingSystem::draw(I_GraphicsHandler& graphics) {
    for (std::map<int, GameObjectStringPair*>::iterator it = targets_.begin(); it != targets_.end(); ++it) {
        SDL_Surface* UIText = TTF_RenderText_Blended(default_font_, it->second->assigned_word_.c_str(), white_);
        graphics.draw(UIText, (int)it->second->game_object_.x_pos(), (int)it->second->game_object_.y_pos(), GraphicPriority::UI);
        SDL_FreeSurface(UIText);
    }
}

const I_Hitbox& TargetingSystem::hitbox() const {
    return hitbox_;
}

void TargetingSystem::notify_collision(GameObject& collided_object) {
    printf("collision with objectid:%d\n", collided_object.id());

    if (targets_.find(collided_object.id()) != targets_.end()) {
        targets_.find(collided_object.id())->second->alive_ = true;
    } else {
        //printf("Target %d was not found. has x: %lf and y: %lf\n", collided_object.id(), collided_object);
        targets_[collided_object.id()] =
            new GameObjectStringPair(grab_word(), collided_object, true);
    }

}

void TargetingSystem::take_damage(int damage) {
    //do nothing;
}


void TargetingSystem::print_dict() {
    for (int i = 0; i < local_dict_.size(); i++) {
        for (int j = 0; j < local_dict_[i].size(); j++) {
            printf("%s\n", local_dict_[i].at(j).c_str());
        }
    }
}

GameObject& TargetingSystem::get_object(std::string word) {
    for (std::map<int, GameObjectStringPair*>::iterator it = targets_.begin(); it != targets_.end(); ++it) {
        if (it->second->assigned_word_.compare(word) == 0) {
            return it->second->game_object_;
        }
    }
}
