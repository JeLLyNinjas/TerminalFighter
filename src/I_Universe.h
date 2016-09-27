#pragma once

#include <memory>

#include "GameObject.h"
#include "Events.h"
#include "DestroyedListener.h"

class I_Universe : public DestroyedListener {
public:
    virtual ~I_Universe() {}
    virtual void get_events() = 0;
    virtual void update_all() = 0;
    virtual void draw_all() = 0;
    virtual void draw_to_screen() = 0;
    virtual void add_game_service(std::unique_ptr<I_Updatable> game_service) = 0;
    virtual void add_game_object(std::unique_ptr<GameObject> game_object) = 0;
    virtual void object_destroyed(int id) = 0;
};
