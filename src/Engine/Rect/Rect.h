#pragma once

#include <SDL2/SDL.h>

typedef struct Rect {
    double x;
    double y;
    double w;
    double h;

    SDL_Rect to_sdl_rect() const {
    	return {
    		(int)(x * 1000000),
    		(int)(y * 1000000),
    		(int)(w * 1000000),
    		(int)(h * 1000000)
    	};
    }
} Rect;

