#pragma once

#include "GameObject.h"

class TargetingSystem : public GameObject {

public:

    TargetingSystem(int word_length_lb, int word_length_ub, std::string color_hex);

    void update();
    virtual void draw(I_GraphicsHandler& graphics);
    virtual const I_Hitbox& hitbox() const;
    virtual void notify_collision(GameObject& collided_object);

private:
	int word_length_lb_;
	int word_length_ub_;
	std::string color_hex_;
};
