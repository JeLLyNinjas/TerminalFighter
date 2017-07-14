#pragma once

#include "GameObject.h"


#include <string>
#include <map>
#include <vector>
#include <fstream>

class TargetingSystem : public GameObject {

public:

    TargetingSystem(int word_length_lb, int word_length_ub, std::string color_hex);

    void update();
    virtual void draw(I_GraphicsHandler& graphics);
    virtual const I_Hitbox& hitbox() const;
    virtual void notify_collision(GameObject& collided_object);

private:

    void setup_dictionary(std::string relative_path);
    std::string grab_word(int lb, int ub);


    std::vector<std::vector<std::string>> local_dict_;

    int word_length_lb_;
    int word_length_ub_;
    std::string color_hex_;
    std::map<int, std::string> targets_;
};
