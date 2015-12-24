#include "delay.h"

Delay::Delay(bool debug_mode) {
    started_ = false;
    debug_mode_ = debug_mode;
    default_delay_font_ = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf", 38);
    lowest_fps = 10000;
}

void Delay::delay_with_fps(double fps) {
    
    if (started_ == false) {
        started_ = true;
        start_timer();
        time_debug = high_resolution_clock::now();
    } else {
        stop_timer(); 
        double time_to_achieve_fps = (1/fps)*1000000;
        time_duration_ = duration_cast<microseconds>(time_end - time_start);
        time_to_achieve_fps = time_to_achieve_fps - time_duration_.count();
        if (time_to_achieve_fps > 0) { 
            usleep(time_to_achieve_fps);
        }
        start_timer();
        if (debug_mode_) {
            printf("Time between loops: %d\n", time_duration_.count());
            printf("Time needed between loops: %lf\n", time_to_achieve_fps);
        }
        time_debug = high_resolution_clock::now();
    }
}

void Delay::start_timer() {
    time_start = high_resolution_clock::now();
}

void Delay::stop_timer() {
    time_end = high_resolution_clock::now();
}

SDL_Surface * Delay::grab_frame_rate() {
    SDL_Color frame_rate_color = {255, 255, 255};
    //time_duration_ = duration_cast<microseconds>(time_end - time_debug);
    

    if (lowest_fps > 1/((double)time_duration_.count()/1000000)) {
        lowest_fps = 1/((double)time_duration_.count()/1000000);
        printf("lowest fps is now %lf\n", lowest_fps);
    }

    return TTF_RenderText_Blended(default_delay_font_, std::to_string(1/((double)time_duration_.count()/1000000)).c_str(), frame_rate_color); 
    
}


