#pragma once
#include <chrono>
#include <unistd.h>

#include <SDL_ttf.h>
#include <SDL2/SDL.h>

using namespace std::chrono;

typedef std::chrono::microseconds us;

class Delay {
public:
    Delay(bool debug_mode);
    void delay_with_fps(double fps);
    SDL_Surface* grab_frame_rate();

private:
    void start_timer();
    void stop_timer();

    high_resolution_clock::time_point time_start, time_end;
    microseconds time_duration_;
    bool started_, debug_mode_;
    double lowest_fps;
    TTF_Font* default_delay_font_;
};
