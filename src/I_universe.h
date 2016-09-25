#pragma once

#include <memory>

#include "game_object.h"
#include "events.h"

class I_Universe
{
public:
	virtual void get_events() = 0;
    virtual void update_all() = 0;
    virtual void draw_all() = 0;
    virtual void draw_to_screen() = 0;
    virtual void add_events_handler(std::unique_ptr<Events> event) = 0;
    virtual void add_game_object(std::unique_ptr<GameObject> game_object) = 0;
};
