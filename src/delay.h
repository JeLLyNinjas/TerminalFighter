#pragma once

#include <chrono>
#include <unistd.h>
#include <iostream>
#include <stdio.h>


using namespace std::chrono;
typedef std::chrono::microseconds us;
class Delay {

public:
    Delay(bool debug_mode);
    void delay_with_fps(double fps);


private:
    void start_timer();
    void stop_timer();
    void sleep(unsigned int microseconds); 
    high_resolution_clock::time_point time_start, time_end;

    bool started_, debug_mode_;
};
