#pragma once

#include <string>
#include <map>
#include <vector>

#include "GameObject/GameObject.h"
#include "Hitbox/Hitbox.h"

struct GameObjectStringPair {
    GameObjectStringPair(std::string word, GameObject& game_object, bool alive)
        : assigned_word_(word)
          //, x_(x)
          //, y_(y)
        , game_object_(game_object)
        , alive_(alive)
    {}

    std::string assigned_word_;
    GameObject& game_object_;
    //double x_;
    //double y_;
    bool alive_;
};

class TargetingSystem : public GameObject {

public:
    TargetingSystem(int word_length_lower_bound, int word_length_upper_bound, std::string color_hex);

    void update();
    virtual void draw(I_GraphicsHandler& graphics);
    virtual const I_Hitbox& hitbox() const;
    virtual void notify_collision(GameObject& collided_object);
    void take_damage(int damage);
    GameObject& get_object(std::string word);

private:
    void setup_local_dict(std::string relative_path);
    std::string grab_word();

    //for debug
    void print_dict();

    Hitbox hitbox_;

    std::vector<std::vector<std::string>> local_dict_;
    std::map<int, GameObjectStringPair*> targets_;
    int word_length_lower_bound_;
    int word_length_upper_bound_;
    std::string color_hex_;

    TTF_Font* default_font_;
};

