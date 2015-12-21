#include "delay.h"

Delay::Delay(bool debug_mode) {
    started_ = false;
    debug_mode_ = debug_mode;
}

void Delay::delay_with_fps(double fps) {
    
    if (started_ == false) {
        started_ = true;
        start_timer();
        std::cout << "first time\n";
    } else {
        std::cout << "Not first time\n";
        stop_timer(); 
        double time_to_achieve_fps = (1/fps)*1000000;
        microseconds time_duration = duration_cast<microseconds>(time_end - time_start);
        printf("Time between loops: %d\n", time_duration.count());
        //printf("Time needed between loops: %lf\n", time_to_achieve_fps);
        usleep(time_to_achieve_fps - time_duration.count());
        start_timer();
    }

    
}

void Delay::start_timer() {
    time_start = high_resolution_clock::now();
}

void Delay::stop_timer() {
    time_end = high_resolution_clock::now();
    
    

}

void Delay::sleep(unsigned int microseconds) {

}


