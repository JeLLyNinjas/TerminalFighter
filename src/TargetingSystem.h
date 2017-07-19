#pragma once

#include "GameObject.h"
#include "Hitbox.h"

#include <string>
#include <map>
#include <vector>

class TargetingSystem : public GameObject {

public:
    TargetingSystem(int word_length_lower_bound, int word_length_upper_bound, std::string color_hex);

    void update();
    virtual void draw(I_GraphicsHandler& graphics);
    virtual const I_Hitbox& hitbox() const;
    virtual void notify_collision(GameObject& collided_object);

private:
    void setup_local_dict(std::string relative_path);
    std::string grab_word(int lower_bound, int upper_bound);

    //for debug
    void print_dict();

    std::vector<std::vector<std::string>> local_dict_;
    std::map<GameObject*, std::vector<std::string>> targets_; //vector will hold two strings, "Name"|"Heartbeat"

    int word_length_lower_bound_;
    int word_length_upper_bound_;
    std::string color_hex_;
    Hitbox hitbox_;
};
