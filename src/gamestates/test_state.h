#pragma once
#include "I_gamestate.h"
#include "delay.h"
#include "game_constants.h"
#include "keyboard_listener.h"
#include "keyboard.h"
#include "missile.h"
#include "missile_launcher.h"
#include "universe.h"
#include "events.h"
#include <SDL2/SDL.h>

class Delay;
class SDL_Renderer;

class TestState : public I_GameState, public KeyboardListener, public EventsListener{
public:
	TestState(SDL_Renderer* renderer);
	gamestates::GameStateName run();
	gamestates::GameStateName name() const;

    /* listeners */
    void notify_keyboard_key_pressed(std::string keypress);
    void notify_events(SDL_Event e);

private:
	void display_debug_frames(Delay *delayer);
	bool exit;

	SDL_Renderer* renderer_;
};
